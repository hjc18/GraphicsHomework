#ifndef PLANE_H
#define PLANE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement Plane representing an infinite plane
// function: ax+by+cz=d
// choose your representation , add more fields and fill in the functions

class Plane : public Object3D {
public:
    Plane() {
        normal = Vector3f::UP;
        offset = 0;
    }

    Plane(const Vector3f &_normal, double d, Material *m) : Object3D(m), offset(d) {
        normal = _normal.normalized();
    }

    ~Plane() override = default;

    bool intersect(const Ray &r, Hit &h, double tmin) override {
        double tt = (offset - Vector3f::dot(normal, r.getOrigin())) / Vector3f::dot(normal, r.getDirection());
        if(tt > tmin && tt < h.getT()){
            h.set(tt, this->material, normal);
            return true;
        }
        return false;
    }

protected:
    Vector3f normal;
    double offset;


};

#endif //PLANE_H
		

