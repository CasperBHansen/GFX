/*
 * Introduction to Computer Graphics
 *
 * DiniSurface.cpp
 *
 */

#include "DiniSurface.h"

#include "utilities/glmutils.h"

DiniSurface::DiniSurface(int N, int M, float a, float b)
    : GeneralSurface(N, M, 0.0f, 6 * M_PI, 0.0001f, 2.0f)
{
    this->a = a;
    this->b = b;
    
    initializeSurface(1);
}

DiniSurface::~DiniSurface()
{
}

glm::vec3 DiniSurface::vertexAt(int part, float u, float v)
{
    part=part; // part is unused for dini surface, silence compiler.
    
    glm::vec3 ret;
    ret.x = a * cosf(u) * sinf(v);
    ret.y = a * sinf(u) * sinf(v);
    ret.z = a * (cosf(v) + logf(tanf(0.5f * v))) + b * u;
    return ret;
}

glm::vec3 DiniSurface::normalAt(int part, float u, float v)
{
    part=part; // part is unused for dini surface, silence compiler.
    
    glm::vec3 du, dv;
    
    du.x = -a * sinf(u) * sinf(v);
    du.y =  a * cosf(u) * sinf(v);
    du.z = b;
    
    dv.x = a * cosf(u) * cosf(v);
    dv.y = a * sinf(u) * sinf(v);
    dv.z = a * ( (0.5f / (sinf(0.5f * v) * cosf(0.5f * v))) - sinf(v));
    
    return glm::normalize( glm::cross(du, dv) );
}

