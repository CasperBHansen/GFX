/*
	Author: Mads Jeppe Lyngholm Rønnow
	Date: 10-Feb-2014
*/

#include "GLLineGrid.h"

void GLLineGrid::draw() { 

	///LEGACY OPENGL UGH!!! ONLY USED HERE TO AVOID COMPLICATING THE CODE WITH SHADERS
	///
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLineWidth(1.0f);
	///

	if (m_hardwareShaderSupport) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_LINES, 0, m_numberOfLinesPerAxis*4);

		glDisableVertexAttribArray(0);
	}
	else {
		//Use legacy OpenGL
		glBegin(GL_LINES);	
		for(int i = 0; i <= m_numberOfLinesPerAxis; i++) {
			float lineX = (float)i*m_gridCellSize - (float)m_numberOfLinesPerAxis*m_gridCellSize*0.5f;

			//Vertical line:
			glVertex2f(lineX, -1.0f);
			glVertex2f(lineX, 1.0f);

			//Horizontal line:
			glVertex2f(-1.0f, lineX);
			glVertex2f(1.0f, lineX);
		}
		glEnd();

		glFlush();
	}
}

void GLLineGrid::initializeBuffers(bool hardwareShaderSupport, float gridCellSize) {
	m_gridCellSize = gridCellSize;
	m_numberOfLinesPerAxis = (1.0f/m_gridCellSize)*2.0;
	m_hardwareShaderSupport = hardwareShaderSupport;

	if (m_hardwareShaderSupport) {
		std::vector<float> vertices;

		for(int i = 0; i <= m_numberOfLinesPerAxis; i++) {
			float lineX = (float)i*m_gridCellSize - (float)m_numberOfLinesPerAxis*m_gridCellSize*0.5f;

			//Vertical line:
			vertices.push_back(lineX);
			vertices.push_back(-1.0f);

			vertices.push_back(lineX);
			vertices.push_back(1.0f);

			//Horizontal line:
			vertices.push_back(-1.0f);
			vertices.push_back(lineX);

			vertices.push_back(1.0f);
			vertices.push_back(lineX);
		}

 		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
	}
}