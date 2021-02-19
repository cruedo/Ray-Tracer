#include <math.h>

#include "Vec3.hpp"

using namespace std;


double abs(Vec3 &V) {
    return sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
}
double Dot(Vec3 A, Vec3 B) {
    return A.x*B.x+A.y*B.y+A.z*B.z;
}

Vec3& Vec3::operator+=(Vec3 &B) {
    x += B.x, y += B.y, z += B.z;
    return *this;
}

Vec3& Vec3::operator*=(double k) {
    x *= k, y *= k, z *= k;
    return *this;
}
Vec3& Vec3::operator/=(double k) {
    x /= k, y /= k, z /= k;
    return *this;
}
Vec3& Vec3::operator-=(Vec3 &B) {
    x -= B.x, y -= B.y, z -= B.z;
    return *this;
}

Vec3 operator+(Vec3 &A, Vec3 &B) {
    Vec3 C = {A.x+B.x, A.y+B.y, A.z+B.z};
    return C;
}
Vec3 operator-(Vec3 &A, Vec3 &B) {
    Vec3 C = {A.x-B.x, A.y-B.y, A.z-B.z};
    return C;
}
Vec3 operator*(Vec3 &A, double k) {
    Vec3 C = {k*A.x, k*A.y, k*A.z};
    return C;
}

ostream& operator<<(ostream &oss, Vec3 &P) {
    oss << "[" << P.x << " " << P.y << " " << P.z << "]";
    return oss; 
}