#include "GLLine.h"


void GLLine::draw(int startX, int startY, int endX, int endY) { 

	///LEGACY OPENGL UGH!!! ONLY USED HERE TO AVOID COMPLICATING THE CODE WITH SHADERS
	///
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef((float) startX*m_gridCellSize,  (float) startY*m_gridCellSize, 0.0f);

	glLineWidth(3.0f);

	float diffX = endX - startX;
	float diffY = endY - startY;

	float distance = distanceBetweenPoints(startX, startY, endX, endY);
	if (distance == 0.0f) 
		return;

	float angle = atan2(diffY, diffX) * 180.0f/PI;
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glScalef(distance,distance,distance);
	///

	if (m_hardwareShaderSupport) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_LINES, 0, 2);

		glDisableVertexAttribArray(0);
	}
	else {
		//Use legacy OpenGL
		glBegin(GL_LINES);	
		glVertex2f(0.0f, 0.0f);
		glVertex2f(m_gridCellSize, 0.0f);
		glEnd();

		glFlush();
	}
}

void GLLine::initializeBuffers(bool hardwareShaderSupport, float gridCellSize) {
	m_hardwareShaderSupport = hardwareShaderSupport;
	m_gridCellSize = gridCellSize;

	float vertices[4] = { 
		0.0f, 0.0f,
		m_gridCellSize, 0.0f
	};

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4, vertices, GL_STATIC_DRAW);
}

