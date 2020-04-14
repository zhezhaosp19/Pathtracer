<h1 align="middle">PathTracer</h1>
    
In this project, I build a renderer that uses ray tracing to render images simulating physical lighting in the reality. I accelerate the renderer largely by implementing Bounding Volume Hierarchy and simulate direct illuminance (including uniform hemisphere sampling and importance sampling) and indirect illuminance based on the bounces of radiance. I learn a lot how the ray tracing works and how lighting working to render a good and real image.

<h2 align="middle">Part 1: Ray Generation and Intersection</h2>

The part1 of the assignment starts with the implementation of ray tracing in each pixel. There are ns_aa random rays going through the image space, I get one random sample in each pixel the ray goes through by calling gridSampler->get_sample() and get each ray by calling camera->generate_ray(). I sum up all the radiance of these rays and average it, then update the color of the samplebuffer. 

Generating ray is to convert the position of a ray from camera space into world space. Because the coordinates in camera space is different from coordinates in image space, we need to compute the corresponding position in the camera space based on the coordinates in image space. Then, once there is a ray, I convert the direction vector of it from camera space into world space by multiplying c2w. 

The primitive intersection is the basic of ray generation. Rays are calculated by the origin point, time and direction vector. When they hit objects, there are different t values indicating different intersection points. The valid t values are those between min_t and max_t that the ray can be seen in the camera. What I want is the nearest the intersection points. Therefore, each time there is an intersection, I update the max_t to be that t that generates this intersection point.


I use Möller Trumbore Algorithm for the triangle intersection algorithm, determining whether there is an intersection with the triangle. 

Firstly, as I mentioned before, Ray is computed as o+td where o is the origin point, t is time, d is direction, and also can be calculated in Barycentric Coordinate with three vertices of the triangle (1 – b1- b2)*P1 + b1*P2 + b2*P3. t, b1 and b2 can be represent as the cross product and dot product of different vectors. 

Secondly, compute the normal of the triangle with Barycentric Coordinate (1 – b1- b2)*n1 + b1*n2 + b2*n3 where n1, n2, n3 are the normal of vertices.

Finally, update the max_t to the new t and also update the n, t, primitive and bsdf of the intersection points.

![library](https://github.com/cal-cs184-student/p3-1-pathtracer-sp20-zhezhaosp19/tree/master/docs/images/part1/CBspheres.png)

<div align="center">
            <table style="width=100%">
                <tr>
                  <td>
                    <img src="https://github.com/zhezhaosp19/Path-Tracer/tree/master/docs/images/part1/CBspheres.png" align="middle" width="400px" />
                    <figcaption align="middle">CBspheres_lambertian.dae</figcaption>
                  </td>
                  <td>
                    <img src="https://github.com/zhezhaosp19/Path-Tracer/tree/master/docs/images/part1/CBgems.png" align="middle" width="400px" />
                    <figcaption align="middle">CBgems.dae</figcaption>
                  </td>
                  <td>
                    <img src="https://github.com/zhezhaosp19/Path-Tracer/tree/master/docs/images/part1/cow.png" align="middle" width="400px" />
                    <figcaption align="middle">cow.dae</figcaption>
                  </td>
                </tr>
            </table>
        </div>
        
<h2 align="middle">Part 2: Bounding Volume Hierarchy</h2>

In the part2, I implement Bounding Volume Hierarchy (BVH) in order to accelerate the ray tracing. BVH is a binary tree structure where there is a rood node and followed by left and right child node. The internal nodes store bounding boxes, and left and right child nodes, while leaf nodes store bounding box and list of objects. 

