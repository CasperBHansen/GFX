/*
 * Types.cpp
 *
 * Defines the output stream operator overloading functions.
 */

#include "Types.h"

std::ostream& operator<<(std::ostream& os, const Point2D &point)
{
    return os << '(' << point.x << ',' << point.y << ')';
}

std::ostream& operator<<(std::ostream& os, const Vector2D &vector)
{
    return os << '(' << vector.x << ',' << vector.y << ')';
}

