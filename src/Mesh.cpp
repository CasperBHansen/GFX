/*
 * Introduction to Computer Graphics
 *
 * Mesh.cpp
 *
 */

#include "Mesh.h"

#include <glm/glm.hpp>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <fstream>

typedef struct {
	int v, vt, vn;
} Index;

typedef struct {
	Index a, b, c;
} Face;

Mesh::Mesh(const char * filename)
{
	valid = false;
	
	// open file
    string line;
    std::ifstream in(filename);
	if ( !in.is_open() ) {
		cerr << "Couldn't read file '" << filename << "', failed to create mesh." << endl;
		exit(EXIT_FAILURE);
	}
	
	// parse file
	vector<glm::vec3> vertices;
	vector<glm::vec3> tex_coords;
	vector<glm::vec3> normals;

	vector<GLuint> f_v;
	vector<GLuint> f_vt;
	vector<GLuint> f_vn;
	
	vector<glm::vec3> v;
	vector<glm::vec3> vt;
	vector<glm::vec3> vn;
	
	vector<Face> faces;
	
	glm::vec3 coord;
	Face face;
	
	int i;
    while ( std::getline(in, line) ) {
		
		i = 0;
		
		// vertices, tex coords and normals
		if ( line[i] == 'v' ) {
			
			while (line[i++] != ' ') {}
			
			sscanf( (line.substr(i, line.length() - i)).c_str(), "%f %f %f",
				&coord.x, &coord.y, &coord.z);
			if (line[1] == ' ') v.push_back(coord);
			if (line[1] == 'n') vn.push_back(coord);
			if (line[1] == 't') vt.push_back(coord);

			continue;
		}
		
		// faces
		if ( line[i] == 'f' ) {
			
			sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&face.a.v, &face.a.vt, &face.a.vn,
				&face.b.v, &face.b.vt, &face.b.vn,
				&face.c.v, &face.c.vt, &face.c.vn);
			
			faces.push_back(face);
			
			continue;
		}
    }
	
	in.close();
	
	// process for OpenGL
	for (i = 0; i < (int)faces.size(); i++) {
		vertices.push_back( v[faces[i].a.v - 1] );
		vertices.push_back( v[faces[i].b.v - 1] );
		vertices.push_back( v[faces[i].c.v - 1] );
		
		if (vn.size() == 0) {
			// no normals in obj-file, compute them
		}
		else {
			normals.push_back( vn[faces[i].a.vn - 1] );
			normals.push_back( vn[faces[i].b.vn - 1] );
			normals.push_back( vn[faces[i].c.vn - 1] );
		}
		
		tex_coords.push_back( vt[faces[i].a.vt - 1] );
		tex_coords.push_back( vt[faces[i].b.vt - 1] );
		tex_coords.push_back( vt[faces[i].c.vt - 1] );
	}
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(BUFFER_COUNT, buffers);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * tex_coords.size(), &tex_coords[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	
	num_vertices = vertices.size();
	valid = true;
}

Mesh::~Mesh()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glDeleteBuffers(BUFFER_COUNT, buffers);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::render()
{
	if (!valid) return;
	
	glBindVertexArray(vao);
	
	for (int id = 0; id < BUFFER_COUNT; ++id) {
		glEnableVertexAttribArray(id);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[id]);
		glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glDrawArrays(GL_TRIANGLES, 0, num_vertices);
	
	glBindVertexArray(0);
}

