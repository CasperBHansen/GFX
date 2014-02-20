/*
 * Types.cpp
 *
 * Defines the output stream operator overloading functions.
 */

#include "Types.h"

std::ostream& operator<<(std::ostream& os, const Vector &vector)
{
    return os << '(' << vector.x << ',' << vector.y << ',' << vector.z << ')';
}

