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

VertexBufferObject::VertexBufferObject(GLenum type, GLfloat * vertices, GLuint count, Shader * shader)
{
    this->type  = type;
    this->count = count;
    this->shader = shader;
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    vtxAttrib = shader->getAttribLocation("vtx");
}

VertexBufferObject::~VertexBufferObject()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
}

void VertexBufferObject::draw()
{
    glVertexAttribPointer(vtxAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vtxAttrib);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(vtxAttrib);
}

