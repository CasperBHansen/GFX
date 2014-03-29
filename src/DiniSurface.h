/*
 * Introduction to Computer Graphics
 *
 * DiniSurface.h
 *
 */

#ifndef DINISURFACE_H
#define DINISURFACE_H

#include "GeneralSurface.h"

class DiniSurface : public GeneralSurface
{
public:
	DiniSurface(int N, int M, float a, float b);
	~DiniSurface();

protected:
    glm::vec3 vertexAt(int part, float u, float v);
    glm::vec3 normalAt(int part, float u, float v);
    
private:
    float a, b;
};

#endif // DINISURFACE_H

