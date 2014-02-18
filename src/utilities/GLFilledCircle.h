/*
	Author: Mads Jeppe Lyngholm Rønnow
	Date: 10-Feb-2014
*/

#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <math.h>

class GLFilledCircle {
public:
	GLFilledCircle();
	
	void draw(int x, int y);
	void initializeBuffers(bool hardwareShaderSupport, float radius);

	~GLFilledCircle() {};

private: 
	GLuint m_VBO;
	int m_numberOfVertices;

	float m_radius;
	float m_centerX, m_centerY;

	bool m_hardwareShaderSupport;

	int m_numberOfEdges;
	float PI;
};

