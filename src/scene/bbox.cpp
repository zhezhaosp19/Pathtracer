#include "bbox.h"

#include "GL/glew.h"

#include <algorithm>
#include <iostream>

namespace CGL {

bool BBox::intersect(const Ray& r, double& t0, double& t1) const {

  // TODO (Part 2.2):
  // Implement ray - bounding box intersection test
  // If the ray intersected the bounding box within the range given by
  // t0, t1, update t0 and t1 with the new intersection times.
    double x1 = (max.x - r.o.x) / r.d.x;
    double y1 = (max.y - r.o.y) / r.d.y;
    double z1 = (max.z - r.o.z) / r.d.z;

    double x2 = (min.x - r.o.x) / r.d.x;
    double y2 = (min.y - r.o.y) / r.d.y;
    double z2 = (min.z - r.o.z) / r.d.z;
    
    double tmax_x = std::max(x1, x2);
    double tmin_x = std::min(x1, x2);
    
    double tmax_y = std::max(y1, y2);
    double tmin_y = std::min(y1, y2);

    double tmax_z = std::max(z1, z2);
    double tmin_z = std::min(z1, z2);
    
    double tmax = std::min(std::min(tmax_x, tmax_y), tmax_z);
    double tmin = std::max(std::max(tmin_x, tmin_y), tmin_z);

    if(tmin <= tmax) {
        t0 = tmin;
        t1 = tmax;
        return true;
    }

    return false;
}

void BBox::draw(Color c, float alpha) const {

  glColor4f(c.r, c.g, c.b, alpha);

  // top
  glBegin(GL_LINE_STRIP);
  glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(max.x, max.y, max.z);
  glEnd();

  // bottom
  glBegin(GL_LINE_STRIP);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, min.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, min.y, min.z);
  glEnd();

  // side
  glBegin(GL_LINES);
  glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(min.x, min.y, max.z);
  glEnd();

}

std::ostream& operator<<(std::ostream& os, const BBox& b) {
  return os << "BBOX(" << b.min << ", " << b.max << ")";
}

} // namespace CGL
