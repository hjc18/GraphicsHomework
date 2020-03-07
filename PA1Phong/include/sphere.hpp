#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement functions and add more fields as necessary

class Sphere : public Object3D {
public:
    Sphere() {
        // unit ball at the center
        center = Vector3f::ZERO;
        radius = 1;
        material = nullptr;
    }

    explicit Sphere(const Vector3f &center, double radius, Material *material) : Object3D(material), center(center), radius(radius) {
        // 
    }

    ~Sphere() override = default;

    bool intersect(const Ray &r, Hit &h, double tmin) override {
        //Ray.direction unit!
        Vector3f o2center = center - r.getOrigin();
        if(h.getT() < o2center.length() - radius) return false;//impossible, too far
        double tmp = Vector3f::dot(o2center, r.getDirection());
        if(tmp <= 0) return false;//angle between ray and center >= 90
        double dis = rtTriangle(tmp, o2center.length(), 1);
        if(dis > radius) return false;//no intersection
        double tt = tmp - rtTriangle(dis, radius, 1);
        if(tt > tmin && tt < h.getT()){
            h.set(tt, this->material, r.pointAtParameter(tt)-center);//normalize inside the function
            return true;
        }
        return false;
    }

protected:
    Vector3f center;
    double radius;

};


#endif
