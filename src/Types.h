/*
 * Types.h
 *
 * Declares basic types used throughout the project.
 */

#ifndef TYPES_H
#define TYPES_H

#include <iostream>

struct Vector {
    float x, y, z, w;
    
    Vector(float x = 0.0f, float y = 0.0f, float z = 0.0f)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = 1.0f;
    }
};


// declare prototypes of operator overloading
std::ostream& operator<<(std::ostream& os, const Vector &vector);

#endif // TYPES_H

