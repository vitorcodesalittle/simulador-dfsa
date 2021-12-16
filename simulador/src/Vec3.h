//
// Created by vilma on 12/15/21.
//

#ifndef SIMULADOR_DFSA_VEC3_H
#define SIMULADOR_DFSA_VEC3_H


class Vec3 {
public:
    double x,y,z;
    Vec3(double x, double y, double z): x{x}, y{x}, z{z} {}
    inline Vec3 operator - (const Vec3 &b) const {
        return Vec3 {x - b.x, y - b.y, z - b.z };
    }
    inline double len () {
        return sqrt(x * x + y * y + z * z);
    }
};


#endif //SIMULADOR_DFSA_VEC3_H
