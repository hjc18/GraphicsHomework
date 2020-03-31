#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include <vecmath.h>
#include <cmath>


class Camera {
public:
    Camera(const Vector3f &center, const Vector3f &direction, const Vector3f &up, int imgW, int imgH) {
        this->center = center;
        //unit axes
        this->direction = direction.normalized();
        this->horizontal = Vector3f::cross(this->direction, up.normalized());
        this->up = Vector3f::cross(this->horizontal, this->direction);
        this->width = imgW;
        this->height = imgH;
    }

    // Generate rays for each screen-space coordinate
    virtual Ray generateRay(const Vector2f &point) = 0;
    virtual ~Camera() = default;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

protected:
    // Extrinsic parameters
    Vector3f center;
    Vector3f direction;
    Vector3f up;
    Vector3f horizontal;
    // Intrinsic parameters
    int width;
    int height;
};

// TODO: Implement Perspective camera
// You can add new functions or variables whenever needed.
class PerspectiveCamera : public Camera {

public:
    PerspectiveCamera(const Vector3f &center, const Vector3f &direction,
            const Vector3f &up, int imgW, int imgH, double angle) : Camera(center, direction, up, imgW, imgH), angle(angle) {
        // angle is in radian.
    }

    Ray generateRay(const Vector2f &point) override {
        double x = ((2.0 * point.x() / width) - 1) * tan(angle / 2.0);
        double y = ((2.0 * point.y() / height) - 1) * tan(angle / 2.0);
        Vector3f d(x, y, 1);
        //transform
        Matrix3f rot(horizontal, up, direction);
        d = (rot * d).normalized();
        return Ray(center, d);
    }

private:
    double angle;

};

#endif //CAMERA_H
