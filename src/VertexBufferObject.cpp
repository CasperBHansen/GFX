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

VertexBufferObject::VertexBufferObject(GLenum type, GLfloat * vertices, GLsizei size, GLuint count)
{
    this->type  = type;
    this->count = count;
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
}

void VertexBufferObject::render(GLuint vtxAttrib)
{
    glVertexAttribPointer(vtxAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(vtxAttrib);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(type, 0, count);
    
    glDisableVertexAttribArray(vtxAttrib);
}

