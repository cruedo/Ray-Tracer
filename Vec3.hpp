#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vec3 {
public:
    double x;
    double y;
    double z;


    Vec3& operator+=(Vec3 &B);
    Vec3& operator*=(double k);
    Vec3& operator/=(double k);
    Vec3& operator-=(Vec3 &B);

    friend Vec3 operator+(Vec3 &A, Vec3 &B);
    friend Vec3 operator-(Vec3 &A, Vec3 &B);
    friend Vec3 operator*(Vec3 &A, double k);
    friend std::ostream& operator << (std::ostream &oss, Vec3 &P);
};


#endif