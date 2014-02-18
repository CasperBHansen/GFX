/*
	Author: Mads Jeppe Lyngholm Rønnow
	Date: 10-Feb-2014
*/

#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>

class GLLineGrid {
public:
	GLLineGrid() {};

	void draw();
	void initializeBuffers(bool hardwareShaderSupport, float gridCellSize);

	~GLLineGrid() {};

private: 
	GLuint m_VBO;
	int m_numberOfVertices;
	float m_gridCellSize;
	float m_numberOfLinesPerAxis;

	bool m_hardwareShaderSupport;
};