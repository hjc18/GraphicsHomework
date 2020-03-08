#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// TODO: implement this class and add more fields as necessary,
class Triangle: public Object3D {

public:
	Triangle() = delete;

    // a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m) : Object3D(m) {
	    vertices[0] = a;
	    vertices[1] = b;
	    vertices[2] = c;
	    normal = Vector3f::cross(b-a, c-a).normalized();
	}

	bool intersect( const Ray& r,  Hit& h , double tmin) override {
	    double offset = Vector3f::dot(vertices[0], normal);
        double tt = (offset - Vector3f::dot(normal, r.getOrigin())) / Vector3f::dot(normal, r.getDirection());
        Vector3f p = r.pointAtParameter(tt);
        for (int i = 0; i < 3; ++i) {
            Vector3f n1 = Vector3f::cross(vertices[i]-p, vertices[(i+1)%3]-p).normalized();
            if(Vector3f::dot(n1, normal) < 0.99) return false;
        }
        if(tt > tmin && tt < h.getT()){
            h.set(tt, this->material, normal);
            return true;
        }
        return false;
	}
	Vector3f normal;
	Vector3f vertices[3];
protected:


};

#endif //TRIANGLE_H
