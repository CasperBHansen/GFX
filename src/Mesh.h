/*
 * Introduction to Computer Graphics
 *
 * Mesh.h
 *
 */

#ifndef MESH_H
#define MESH_H

#include "Object.h"

#include <GL/glew.h>

typedef enum {
	VERTEX_BUFFER,
	NORMAL_BUFFER,
	TEXCOORD_BUFFER
} BufferId;

#define BUFFER_COUNT 3

class Mesh : public Object
{
public:
	Mesh(const char * filename);
	~Mesh();
	
	void render();

protected:
private:
	GLuint vao;
	GLuint buffers[BUFFER_COUNT];
	
	GLuint num_vertices;
	bool valid;
};

#endif // MESH_H

