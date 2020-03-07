#ifndef VECTOR_3F_H
#define VECTOR_3F_H
#include <iostream>
#include <cmath>
class Vector2f;

class Vector3f
{
public:

	static const Vector3f ZERO;
	static const Vector3f UP;
	static const Vector3f RIGHT;
	static const Vector3f FORWARD;

    Vector3f( double f = 0.f );
    Vector3f( double x, double y, double z );

	Vector3f( const Vector2f& xy, double z );
	Vector3f( double x, const Vector2f& yz );

	// copy constructors
    Vector3f( const Vector3f& rv );

	// assignment operators
    Vector3f& operator = ( const Vector3f& rv );

	// no destructor necessary

	// returns the ith element
    const double& operator [] ( int i ) const;
    double& operator [] ( int i );

    double& x();
	double& y();
	double& z();

	double x() const;
	double y() const;
	double z() const;

	Vector2f xy() const;
	Vector2f xz() const;
	Vector2f yz() const;

	Vector3f xyz() const;
	Vector3f yzx() const;
	Vector3f zxy() const;

	double length() const;
    double squaredLength() const;

	void normalize();
	Vector3f normalized() const;

	Vector2f homogenized() const;

	void negate();

	// ---- Utility ----
    operator const double* () const; // automatic type conversion for OpenGL
    operator double* (); // automatic type conversion for OpenGL
	void print() const;	

	Vector3f& operator += ( const Vector3f& v );
	Vector3f& operator -= ( const Vector3f& v );
    Vector3f& operator *= ( double f );

    static double dot( const Vector3f& v0, const Vector3f& v1 );
	static Vector3f cross( const Vector3f& v0, const Vector3f& v1 );
    
    // computes the linear interpolation between v0 and v1 by alpha \in [0,1]
	// returns v0 * ( 1 - alpha ) * v1 * alpha
	static Vector3f lerp( const Vector3f& v0, const Vector3f& v1, double alpha );

	// computes the cubic catmull-rom interpolation between p0, p1, p2, p3
    // by t \in [0,1].  Guarantees that at t = 0, the result is p0 and
    // at p1, the result is p2.
	static Vector3f cubicInterpolate( const Vector3f& p0, const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, double t );

private:

	double m_elements[ 3 ];

};

// component-wise operators
Vector3f operator + ( const Vector3f& v0, const Vector3f& v1 );
Vector3f operator - ( const Vector3f& v0, const Vector3f& v1 );
Vector3f operator * ( const Vector3f& v0, const Vector3f& v1 );
Vector3f operator / ( const Vector3f& v0, const Vector3f& v1 );
inline double Euclid(const Vector3f& v0, const Vector3f& v1)
{
    return sqrt((v0.x()-v1.x()) * (v0.x()-v1.x())
                + (v0.y()-v1.y()) * (v0.y()-v1.y())
                + (v0.z()-v1.z()) * (v0.z()-v1.z()));
}

inline double rtTriangle(double l0, double l1, int hypoIndex = 2){
    switch(hypoIndex){
        case 0:
            return sqrt(l0*l0 - l1*l1);
        case 1:
            return sqrt(l1*l1 - l0*l0);
        case 2:
            return sqrt(l0*l0 + l1*l1);
        default:
            return 0;
    }
}

// unary negation
Vector3f operator - ( const Vector3f& v );

// multiply and divide by scalar
Vector3f operator * ( double f, const Vector3f& v );
Vector3f operator * ( const Vector3f& v, double f );
Vector3f operator / ( const Vector3f& v, double f );

bool operator == ( const Vector3f& v0, const Vector3f& v1 );
bool operator != ( const Vector3f& v0, const Vector3f& v1 );

inline std::ostream &operator<<(std::ostream &os, const Vector3f& v) {
    os << "[" << v.x() << ", " << v.y() << ", " << v.z() << "]";
    return os;
}
inline double max(double x, double y){
    return x > y ? x : y;
}
inline double mpow(double x, int exp){
    double result = 1;
    while(exp--){
        result *= x;
    }
    return result;
}
#endif // VECTOR_3F_H
