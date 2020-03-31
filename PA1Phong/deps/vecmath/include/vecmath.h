#ifndef VECMATH_H
#define VECMATH_H

#include "Matrix2f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "Quat4f.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"
inline double max(double x, double y){
    return x > y ? x : y;
}
inline double min(double x, double y){
    return x < y ? x : y;
}
inline void swap(double& x, double& y){
    double tmp = x;
    x = y;
    y = tmp;
}
#endif // VECMATH_H
