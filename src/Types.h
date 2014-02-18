/*
 * Types.h
 *
 * Declares basic types used throughout the project.
 */

#ifndef TYPES_H
#define TYPES_H

#include <iostream>

struct Point2D {
    int x, y;
    
    Point2D(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    }
};

struct Vector2D {
    float x, y;
    
    Vector2D(float x = 0.0f, float y = 0.0f)
    {
        this->x = x;
        this->y = y;
    }
};


// declare prototypes of operator overloading
std::ostream& operator<<(std::ostream& os, const Point2D &point);
std::ostream& operator<<(std::ostream& os, const Vector2D &vector);

#endif // TYPES_H

