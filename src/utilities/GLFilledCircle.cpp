/*
	Author: Mads Jeppe Lyngholm Rønnow
	Date: 10-Feb-2014
*/

#include "GLFilledCircle.h"


GLFilledCircle::GLFilledCircle(void) {
	m_radius = 0.05f;
	m_centerX = 0.0f;
	m_centerY = 0.0f;

	m_numberOfVertices = 30;

	PI = (float) acos(-1.0);
}

void GLFilledCircle::draw(int x, int y) {

	///LEGACY OPENGL UGH!!! ONLY USED HERE TO AVOID COMPLICATING THE CODE WITH SHADERS
	///
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef((float) x*m_radius*2.0f,  (float) y*m_radius*2.0f, 0.0f);
	///

	if (m_hardwareShaderSupport) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLE_FAN, 0, m_numberOfVertices);

		glDisableVertexAttribArray(0);
	}
	else {
		//Use legacy OpenGL
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(m_centerX, m_centerY);

		for(int i = 0; i <= m_numberOfEdges; i++) {
			float circleStepX = m_centerX + m_radius * cos(2*PI * (float)i/(float)m_numberOfEdges);
			float circleStepY = m_centerY + m_radius * sin(2*PI * (float)i/(float)m_numberOfEdges);

			glVertex2f(circleStepX, circleStepY);
		}
		glEnd();
	}
}

void GLFilledCircle::initializeBuffers(bool hardwareShaderSupport, float radius) {
	m_radius = radius;
	m_numberOfEdges = m_numberOfVertices-2;
	m_hardwareShaderSupport = hardwareShaderSupport;

	if (m_hardwareShaderSupport) {
		std::vector<float> vertices;

		vertices.push_back(m_centerX);
		vertices.push_back(m_centerY);

		for(int i = 0; i <= m_numberOfEdges; i++) {
			float circleStepX = m_centerX + m_radius * cos(2*PI * (float)i/(float)m_numberOfEdges);
			float circleStepY = m_centerY + m_radius * sin(2*PI * (float)i/(float)m_numberOfEdges);

			vertices.push_back(circleStepX);
			vertices.push_back(circleStepY);
		}

 		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
	}
}
