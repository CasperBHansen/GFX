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
	VertexBufferObject(GLenum type, GLfloat * vertices, GLsizei size, GLuint count);
	~VertexBufferObject();
    
    void render(GLuint vtxAttrib);

protected:
private:
    GLenum type;
    GLuint count;
    
    GLuint vbo;
    GLuint vtxAttrib;
};

#endif // VERTEXBUFFEROBJECT_H

