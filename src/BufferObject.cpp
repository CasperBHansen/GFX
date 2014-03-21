/*
 * Introduction to Computer Graphics
 *
 * BufferObject.cpp
 *
 */

#include "BufferObject.h"

#include <iostream>

BufferObject::BufferObject(GLuint count)
{
    this->count = count;
    
    buffers = (GLuint *)malloc(sizeof(GLuint) * count);
    
    glGenBuffers(count, buffers);
}

BufferObject::~BufferObject()
{
    glDeleteBuffers(count, buffers);
    
    free(buffers);
    buffers = NULL;
}

GLuint BufferObject::getBuffer(int index)
{
    return buffers[index];
}

