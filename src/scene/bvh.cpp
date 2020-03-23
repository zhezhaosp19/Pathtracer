#include "bvh.h"

#include "CGL/CGL.h"
#include "triangle.h"

#include <iostream>
#include <stack>

using namespace std;

namespace CGL {
namespace SceneObjects {

BVHAccel::BVHAccel(const std::vector<Primitive *> &_primitives,
                   size_t max_leaf_size) {

  primitives = std::vector<Primitive *>(_primitives);
  root = construct_bvh(primitives.begin(), primitives.end(), max_leaf_size);
}

BVHAccel::~BVHAccel() {
  if (root)
    delete root;
  primitives.clear();
}

BBox BVHAccel::get_bbox() const { return root->bb; }

void BVHAccel::draw(BVHNode *node, const Color &c, float alpha) const {
  if (node->isLeaf()) {
    for (auto p = node->start; p != node->end; p++) {
      (*p)->draw(c, alpha);
    }
  } else {
    draw(node->l, c, alpha);
    draw(node->r, c, alpha);
  }
}

void BVHAccel::drawOutline(BVHNode *node, const Color &c, float alpha) const {
  if (node->isLeaf()) {
    for (auto p = node->start; p != node->end; p++) {
      (*p)->drawOutline(c, alpha);
    }
  } else {
    drawOutline(node->l, c, alpha);
    drawOutline(node->r, c, alpha);
  }
}

BVHNode *BVHAccel::construct_bvh(std::vector<Primitive *>::iterator start,
                                 std::vector<Primitive *>::iterator end,
                                 size_t max_leaf_size) {

  // TODO (Part 2.1):
  // Construct a BVH from the given vector of primitives and maximum leaf
  // size configuration. The starter code build a BVH aggregate with a
  // single leaf node (which is also the root) that encloses all the
  // primitives.


    BBox bbox;
    BBox centroid_b;
    Vector3D cens;
    int size = 0;
    
    for (auto p = start; p != end; p++) {
        BBox bb = (*p)->get_bbox();
        bbox.expand(bb);
        Vector3D cen = bb.centroid();
        cens += cen;
        centroid_b.expand(cen);
        size++;
    }
    

    BVHNode *node = new BVHNode(bbox);

    if(size <= max_leaf_size){
        node->start = start;
        node->end = end;
        return node;
    } else {
    double ex_x = centroid_b.extent.x;
    double ex_y = centroid_b.extent.y;
    double ex_z = centroid_b.extent.z;
    Vector3D sp = cens / size;
    double sp_x = sp.x;
    double sp_y = sp.y;
    double sp_z = sp.z;
//    auto left = new std::vector<Primitive *>;
//    auto right = new std::vector<Primitive *>;

    if(ex_x >= ex_y && ex_x >= ex_z) { // split along x axis
        for(auto p = start; p != end; p++) {
            BBox bb = (*p)->get_bbox();
            Vector3D cen = bb.centroid();
            if(cen.x <= sp_x) {
                node->left.push_back(*p);
//                left->push_back(*p);
            } else {
                node->right.push_back(*p);
//                right->push_back(*p);
            }
        }
    }

    if(ex_y > ex_x && ex_y >= ex_z) { // split along y axis
        for(auto p = start; p != end; p++) {
            BBox bb = (*p)->get_bbox();
            Vector3D cen = bb.centroid();
            if(cen.y <= sp_y) {
                node->left.push_back(*p);
//                left->push_back(*p);
            } else {
                node->right.push_back(*p);
//                right->push_back(*p);
            }
        }
    }

    if(ex_z > ex_y && ex_z > ex_x) { // split along z axis
        for(auto p = start; p != end; p++) {
            BBox bb = (*p)->get_bbox();
            Vector3D cen = bb.centroid();
            if(cen.z <= sp_z) {
                node->left.push_back(*p);
//                left->push_back(*p);
            } else {
                node->right.push_back(*p);
//                right->push_back(*p);
            }
        }
    }

    auto start_l = node->left.begin();
    auto end_l = node->left.end();
    auto start_r = node->right.begin();
    auto end_r = node->right.end();
//    auto start_l = left->begin();
//    auto end_l = left->end();
//    auto start_r = right->begin();
//    auto end_r = right->end();

//        cout<<size<<endl;
    node->l = construct_bvh(start_l, end_l, max_leaf_size);
    node->r = construct_bvh(start_r, end_r, max_leaf_size);
    }
    
    return node;
}

bool BVHAccel::has_intersection(const Ray &ray, BVHNode *node) const {
  // TODO (Part 2.3):
  // Fill in the intersect function.
  // Take note that this function has a short-circuit that the
  // Intersection version cannot, since it returns as soon as it finds
  // a hit, it doesn't actually have to find the closest hit.
    double t0, t1;
    if(node->bb.intersect(ray, t0, t1) == false) {
        return false;
    }
        if(node->isLeaf()) {
            for (auto p = node->start; p != node->end; p++) {
                total_isects++;
                if ((*p)->has_intersection(ray))
                    return true;
            }
        }
        return (has_intersection(ray, node->l) || has_intersection(ray, node->r));
}

bool BVHAccel::intersect(const Ray &ray, Intersection *i, BVHNode *node) const {
  // TODO (Part 2.3):
  // Fill in the intersect function.

    bool hit = false;
    
    double t0, t1;
    if(node->bb.intersect(ray, t0, t1) == false) {
        return false;
    }
    
    if(node->isLeaf()) {
        for (auto p = node->start; p != node->end; p++) {
            total_isects++;
            hit = (*p)->intersect(ray, i) || hit;
        }
    } else {
        bool hit1 = intersect(ray, i, node->l);
        bool hit2 = intersect(ray, i, node->r);
//        cout<<i<<endl;
        return hit1 || hit2;
    }
    return hit;
}

} // namespace SceneObjects
} // namespace CGL
