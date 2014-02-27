/*
 * Introduction to Computer Graphics
 *
 * VertexBufferObject.h
 *
 */

#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <GL/glew.h>

#include "BufferObject.h"

class VertexBufferObject : public BufferObject
{
public:
	VertexBufferObject(GLenum type, GLfloat * vertices, GLuint count);
	~VertexBufferObject();
    
    void render(GLuint vtxAttrib);

protected:
private:
    GLenum type;
    GLuint count;
    
    GLuint vtxAttrib;
};

#endif // VERTEXBUFFEROBJECT_H

