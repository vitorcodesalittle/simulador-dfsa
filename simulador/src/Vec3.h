//
// Created by vilma on 12/15/21.
//

#ifndef SIMULADOR_DFSA_VEC3_H
#define SIMULADOR_DFSA_VEC3_H
#include<math.h>

typedef unsigned long long ull;


class Vec3 {
public:
    double x,y,z;
    Vec3(double x, double y, double z): x{x}, y{x}, z{z} {}
    Vec3(ull xx, ull yy, ull zz) {
        x = static_cast<double>(xx);
        y = static_cast<double>(yy);
        z = static_cast<double>(zz);
    }
    inline Vec3 operator - (const Vec3 &b) const {
        return Vec3 {x - b.x, y - b.y, z - b.z };
    }
    inline double len () {
        return sqrt(x * x + y * y + z * z);
    }
};


#endif //SIMULADOR_DFSA_VEC3_H
