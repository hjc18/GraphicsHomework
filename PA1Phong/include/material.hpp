#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "ray.hpp"
#include "hit.hpp"
#include <iostream>

// TODO: Implement Shade function that computes Phong introduced in class.
class Material {
public:

    explicit Material(const Vector3f &d_color, const Vector3f &s_color = Vector3f::ZERO, double s = 0) :
            diffuseColor(d_color), specularColor(s_color), shininess(s) {

    }

    virtual ~Material() = default;

    virtual Vector3f getDiffuseColor() const {
        return diffuseColor;
    }


    Vector3f Shade(const Ray &ray, const Hit &hit,
                   const Vector3f &dirToLight, const Vector3f &lightColor) {
        Vector3f Ref = (2 * Vector3f::dot(dirToLight, hit.getNormal()) * hit.getNormal()) - dirToLight;
        double cd = max(0, Vector3f::dot(dirToLight, hit.getNormal()));
        double cs = mpow(max(0,  Vector3f::dot(Ref, -ray.getDirection())), shininess);
        return lightColor * (cd * diffuseColor + cs * specularColor);
    }

protected:
    Vector3f diffuseColor;
    Vector3f specularColor;
    double shininess;
};


#endif // MATERIAL_H
