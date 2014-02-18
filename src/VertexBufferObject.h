/*
 * Introduction to Computer Graphics
 *
 * VertexBufferObject.h
 *
 */

#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <GL/glew.h>

#include "Shader.h"

class VertexBufferObject
{
public:
	VertexBufferObject(GLenum type, GLfloat * vertices, GLuint count, Shader * shader);
	~VertexBufferObject();
    
    void draw();

protected:
private:
    GLenum type;
    GLuint count;
    
    GLuint vbo;
    GLuint vtxAttrib;
    
    Shader * shader;
};

#endif // VERTEXBUFFEROBJECT_H

