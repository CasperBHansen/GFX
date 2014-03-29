/*
 * Introduction to Computer Graphics
 *
 * KleinBottle.cpp
 *
 */

#include "KleinBottle.h"

enum {
    PART_BOTTOM,
    PART_HANDLE,
    PART_TOP,
    PART_MIDDLE
};

KleinBottle::KleinBottle(int N, int M)
    : GeneralSurface(N, M, 0, 2 * M_PI, 0, M_PI)
{
    initializeSurface(4);
}

KleinBottle::~KleinBottle()
{
}

glm::vec3 KleinBottle::vertexAt(int part, float u, float v)
{
    glm::vec3 ret;
    
    switch (part)
    {
        case PART_BOTTOM:
            ret.x = (2.5f + 1.5f * cosf(v)) * cosf(u);
            ret.y = (2.5f + 1.5f * cosf(v)) * sinf(u);
            ret.z = -2.5f * sinf(v);
            break;
        
        case PART_HANDLE:
            ret.x = 2.0f - 2.0f * cosf(v) + sinf(u);
            ret.y = cosf(u);
            ret.z = 3.0f * v;
            break;
        
        case PART_TOP:
            ret.x = 2.0f + (2.0f + cosf(u)) * cosf(v);
            ret.y = sinf(u);
            ret.z = 3.0f * M_PI + (2.0f + cosf(u)) * sinf(v);
            break;
        
        case PART_MIDDLE:
            ret.x = (2.5f + 1.5f * cosf(v)) * cosf(u);
            ret.y = (2.5f + 1.5f * cosf(v)) * sinf(u);
            ret.z = 3.0f * v;
            break;
    }
    
    return ret;
}

glm::vec3 KleinBottle::normalAt(int part, float u, float v)
{
    glm::vec3 ret;
    
    switch (part)
    {
        case PART_BOTTOM:
            ret.x = (-6.25f - 3.75f * cosf(v)) * cosf(v) * cosf(u);
            ret.y = (-6.25f - 3.75f * cosf(v)) * cosf(v) * sinf(u);
            ret.z = (3.75f + 2.25f * cosf(v)) * sinf(v);
            break;
        
        case PART_HANDLE:
            ret.x = -3.0f * sinf(u);
            ret.y = -3.0f * cosf(u);
            ret.z = 2.0f * sinf(u) * sinf(v);
            break;
        
        case PART_TOP:
            ret.x = (2.0f + cosf(u)) * cosf(u) * cosf(v);
            ret.y = (2.0f + cosf(u)) * sinf(u);
            ret.z = (2.0f + cosf(u)) * cosf(u) * sinf(v);
            break;
        
        case PART_MIDDLE:
            ret.x = (7.5f + 4.5f * cosf(v)) * cosf(u);
            ret.y = (7.5f + 4.5f * cosf(v)) * sinf(u);
            ret.z = (3.75f + 2.25f * cosf(v)) * cosf(v);
            break;
    }
    
    return glm::normalize(ret);
}

