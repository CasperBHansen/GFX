/*
 * Introduction to Computer Graphics
 *
 * VertexBufferObject.cpp
 *
 */

#include "VertexBufferObject.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

VertexBufferObject::VertexBufferObject(GLenum type, GLfloat * vertices, GLuint count)
                  : BufferObject( (GLuint)1 )
{
    this->type  = type;
    this->count = count;
    
    glBindBuffer(GL_ARRAY_BUFFER, getBuffer(0));
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * count, vertices, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::render(GLuint vtxAttrib)
{
    glBindBuffer(GL_ARRAY_BUFFER, getBuffer(0));
    glVertexAttribPointer(vtxAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    glEnableVertexAttribArray(vtxAttrib);
    
    glDrawArrays(type, 0, count);
    
    glDisableVertexAttribArray(vtxAttrib);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

