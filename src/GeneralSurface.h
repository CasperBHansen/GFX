/*
 * Introduction to Computer Graphics
 *
 * GeneralSurface.h
 *
 */

#ifndef GENERALSURFACE_H
#define GENERALSURFACE_H

#include "Object.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <math.h>

#ifndef BUFFER_COUNT
#define BUFFER_COUNT 3

typedef enum {
	VERTEX_BUFFER,
	NORMAL_BUFFER,
    TEXCOORD_BUFFER
} BufferId;
#endif

class GeneralSurface : public Object
{
public:
    GeneralSurface(int N, int M,
                   float u_min, float u_max,
                   float v_min, float v_max);
    virtual ~GeneralSurface();
    
    void initializeSurface(int parts);
    virtual void render(int mask) const;
    
    virtual glm::vec3 vertexAt(int part, float u, float v) = 0;
    virtual glm::vec3 normalAt(int part, float u, float v) = 0;

protected:
    int N, M;
    float u_min, u_max;
    float v_min, v_max;
    
    GLuint vao;
    GLuint buffers[BUFFER_COUNT];
    
    int num_vertices;
    
private:
};

#endif // GENERALSURFACE_H

