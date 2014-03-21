/*
 * Introduction to Computer Graphics
 *
 * BufferObject.h
 *
 */

#ifndef BUFFEROBJECT_H
#define BUFFEROBJECT_H

#include <GL/glew.h>

class BufferObject
{
public:
	BufferObject(GLuint count);
	~BufferObject();
    
    GLuint getBuffer(int index);

protected:
private:
    GLuint count;
    GLuint * buffers;
};

#endif // BUFFEROBJECT_H

