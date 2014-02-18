/*
	Author: Mads Jeppe Lyngholm Rønnow
	Date: 10-Feb-2014
*/

#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <math.h>

class GLLine {
public:
	GLLine() {
		PI = (float) acos(-1.0);
	};

	void draw(int startX, int startY, int endX, int endY);
	void initializeBuffers(bool hardwareShaderSupport, float gridCellSize);

	inline float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
		return sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	}

	~GLLine() {};

private: 
	GLuint m_VBO;
	int m_numberOfVertices;
	float m_gridCellSize;

	bool m_hardwareShaderSupport;

	float PI;
};
