#include "pathtracer.h"

#include "scene/light.h"
#include "scene/sphere.h"
#include "scene/triangle.h"


using namespace CGL::SceneObjects;

namespace CGL {

PathTracer::PathTracer() {
  gridSampler = new UniformGridSampler2D();
  hemisphereSampler = new UniformHemisphereSampler3D();

  tm_gamma = 2.2f;
  tm_level = 1.0f;
  tm_key = 0.18;
  tm_wht = 5.0f;
}

PathTracer::~PathTracer() {
  delete gridSampler;
  delete hemisphereSampler;
}

void PathTracer::set_frame_size(size_t width, size_t height) {
  sampleBuffer.resize(width, height);
  sampleCountBuffer.resize(width * height);
}

void PathTracer::clear() {
  bvh = NULL;
  scene = NULL;
  camera = NULL;
  sampleBuffer.clear();
  sampleCountBuffer.clear();
  sampleBuffer.resize(0, 0);
  sampleCountBuffer.resize(0, 0);
}

void PathTracer::write_to_framebuffer(ImageBuffer &framebuffer, size_t x0,
                                      size_t y0, size_t x1, size_t y1) {
  sampleBuffer.toColor(framebuffer, x0, y0, x1, y1);
}

Spectrum
PathTracer::estimate_direct_lighting_hemisphere(const Ray &r,
                                                const Intersection &isect) {
  // Estimate the lighting from this intersection coming directly from a light.
  // For this function, sample uniformly in a hemisphere.

  // make a coordinate system for a hit point
  // with N aligned with the Z direction.
    Matrix3x3 o2w;
    make_coord_space(o2w, isect.n);
    Matrix3x3 w2o = o2w.T();

  // w_out points towards the source of the ray (e.g.,
  // toward the camera if this is a primary ray)
    const Vector3D &hit_p = r.o + r.d * isect.t; //in world space
    const Vector3D &w_out = w2o * (-r.d); //in object frame

  // This is the same number of total samples as
  // estimate_direct_lighting_importance (outside of delta lights). We keep the
  // same number of samples for clarity of comparison.
    int num_samples = scene->lights.size() * ns_area_light;
    Spectrum L_out;
    
    Spectrum l;
    Spectrum e;
    
    for(int i = 0; i < num_samples; i++) {
        Vector3D w_in = hemisphereSampler->get_sample(); // in object frame
        Vector3D spdi_w = o2w * w_in; // in world space
//        Vector3D newray_o = hit_p + EPS_D * spdi_w; // in world space
        Ray newray = Ray(hit_p, spdi_w);
        newray.min_t = EPS_F;

        Intersection next_inter;
        if(bvh->intersect(newray, &next_inter)){ //in world space
            l = isect.bsdf->f(w_out, w_in); // in object frame
            e = next_inter.bsdf->get_emission(); // in object frame (emission from next intersection point)
            L_out += l * e * cos_theta(w_in);
        }
    }
    Spectrum lighting = L_out * 2.0 * PI / num_samples;

    return lighting;
}

Spectrum
PathTracer::estimate_direct_lighting_importance(const Ray &r,
                                                const Intersection &isect) {
  // Estimate the lighting from this intersection coming directly from a light.
  // To implement importance sampling, sample only from lights, not uniformly in
  // a hemisphere.

  // make a coordinate system for a hit point
  // with N aligned with the Z direction.
    Matrix3x3 o2w;
    make_coord_space(o2w, isect.n);
    Matrix3x3 w2o = o2w.T();

  // w_out points towards the source of the ray (e.g.,
  // toward the camera if this is a primary ray)
    const Vector3D &hit_p = r.o + r.d * isect.t;
    const Vector3D &w_out = w2o * (-r.d);
    Spectrum L_out;
    int num_samples = ns_area_light;

    Vector3D wi;
    float distToLight;
    float pdf;
    
    for(SceneLight* p: scene->lights) {
        if(p->is_delta_light()) {
            num_samples = 1;
        }
        
        for(int i = 0; i < num_samples; i++) {
            Spectrum sp_l = p->sample_L(hit_p, &wi, &distToLight, &pdf); //in world space
            Vector3D w_in = w2o * wi; // in object frame
            if(w_in.z >= 0) {
                wi.normalize();
//                Vector3D newray_o = hit_p + EPS_D * (wi);
                Ray newray = Ray(hit_p, wi);
                newray.max_t = distToLight - EPS_F;
                newray.min_t = EPS_F;
                
                Intersection next_inter;
                if(!bvh->intersect(newray, &next_inter)){
                    Spectrum l = isect.bsdf->f(w_out, w_in); // in object frame
                    L_out += l * sp_l * cos_theta(w_in);
                }
            }
        }
        L_out = L_out / (pdf * num_samples);
    }
    
    return L_out;
}

Spectrum PathTracer::zero_bounce_radiance(const Ray &r,
                                          const Intersection &isect) {
  // Returns the light that results from no bounces of light
    if(isect.t < r.min_t || isect.t > r.max_t) {
        return Spectrum(0.0);
    }
    return isect.bsdf->get_emission();
//    return Spectrum(1.0);
}

Spectrum PathTracer::one_bounce_radiance(const Ray &r,
                                         const Intersection &isect) {
  // Returns either the direct illumination by hemisphere or importance sampling
  // depending on `direct_hemisphere_sample`
    if(isect.t < r.min_t || isect.t > r.max_t) {
        return Spectrum(0.0);
    }
    if(direct_hemisphere_sample) {
        return estimate_direct_lighting_hemisphere(r, isect);
    } else {
        return estimate_direct_lighting_importance(r, isect);
    }
}

Spectrum PathTracer::at_least_one_bounce_radiance(const Ray &r,
                                                  const Intersection &isect) {
    Matrix3x3 o2w;
    make_coord_space(o2w, isect.n);
    Matrix3x3 w2o = o2w.T();
    
    Vector3D hit_p = r.o + r.d * isect.t; //in world space
    Vector3D w_out = w2o * (-r.d); //in object frame
    
    Spectrum L_out = one_bounce_radiance(r, isect);
    Vector3D w_in; // in object frame
    float pdf;
    w_in.normalize();
    Spectrum bsdf = isect.bsdf->sample_f(w_out, &w_in, &pdf);
    float continuation_probability = 0.7;

    if(max_ray_depth == 0) {
        return zero_bounce_radiance(r, isect);
    }
    if(max_ray_depth <= 1) { // no indirect illumination
        return L_out;
    } else { //indirect illumination is "turned on"
        if(coin_flip(continuation_probability) || r.depth == max_ray_depth) {
            Vector3D wi = o2w * w_in; // in world frame
//            Vector3D newray_o = hit_p + EPS_D * wi;
            Ray newray = Ray(hit_p, wi, (int)r.depth - 1);
            newray.min_t = EPS_F;

            Intersection next_inter;
            if(bvh->intersect(newray, &next_inter)){ //in world space
                Spectrum bounce_radiance = at_least_one_bounce_radiance(newray, next_inter);
                L_out += bsdf * bounce_radiance * cos_theta(w_in) / pdf / continuation_probability;
            }
        }
    }

    return L_out;

}

Spectrum PathTracer::est_radiance_global_illumination(const Ray &r) {
  Intersection isect;
  Spectrum L_out;

  // If no intersection occurs, we simply return black.
  // This changes if you implement hemispherical lighting for extra credit.

    if (!bvh->intersect(r, &isect))
        return L_out;
    
//    L_out = zero_bounce_radiance(r, isect);
    
  // The following line of code returns a debug color depending
  // on whether ray intersection with triangles or spheres has
  // been implemented.

    L_out = zero_bounce_radiance(r, isect) + at_least_one_bounce_radiance(r, isect);
    return L_out;
}

void PathTracer::raytrace_pixel(size_t x, size_t y) {

  // Make a loop that generates num_samples camera rays and traces them
  // through the scene. Return the average Spectrum.
  // You should call est_radiance_global_illumination in this function.

  // Modify your implementation to include adaptive sampling.
  // Use the command line parameters "samplesPerBatch" and "maxTolerance"

    int num_samples = ns_aa;          // total samples to evaluate
    Vector2D origin = Vector2D(x, y); // bottom left corner of the pixel
    double width = sampleBuffer.w;
    double height = sampleBuffer.h;
    Spectrum radiance;
    double s1 = 0;
    double s2 = 0;
    
    int i = 0;
    for(i = 0; i < num_samples; i++) {
        // adaptive sample
        if(i % samplesPerBatch == 0) {
            double mean = s1 / (double)i;
            double sq_standard_deviation = (s2 - s1 * s1 / (double)i) / ((double)i - 1.0);
            double I = 1.96 * sqrt(sq_standard_deviation) / sqrt(i);
            if(I <= maxTolerance * mean) {
                break;
            }
        }

            Vector2D sample = gridSampler->get_sample();
            double cx = (x + sample.x) / width;
            double cy = (y + sample.y) / height;
            Ray r = this->camera->generate_ray(cx, cy);
            r.depth = max_ray_depth;
            Spectrum est_illu = est_radiance_global_illumination(r);
            radiance += est_illu;
        
            s1 += est_illu.illum();
            s2 += est_illu.illum() * est_illu.illum();

    }
    

    radiance = radiance * (1.0 / i);

    sampleBuffer.update_pixel(radiance, x, y);
    sampleCountBuffer[x + y * sampleBuffer.w] = i;
}

} // namespace CGL
