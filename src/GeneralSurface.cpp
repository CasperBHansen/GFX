/*
 * Introduction to Computer Graphics
 *
 * GeneralSurface.cpp
 *
 */

#include "GeneralSurface.h"

#include <iostream>
#include <vector>

GeneralSurface::GeneralSurface(int N, int M,
                               float u_min, float u_max,
                               float v_min, float v_max)
{
    this->N     = N;
    this->M     = M;
    this->u_min = u_min;
    this->u_max = u_max;
    this->v_min = v_min;
    this->v_max = v_max;
    
    std::cout << "Surface Information" << std::endl;
    std::cout << "N: "      << N << std::endl;
    std::cout << "M: "      << M << std::endl;
    std::cout << "u_min: "  << u_min << std::endl;
    std::cout << "u_max: "  << u_max << std::endl;
    std::cout << "v_min: "  << v_min << std::endl;
    std::cout << "v_max: "  << v_max << std::endl;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(BUFFER_COUNT, buffers);
}

GeneralSurface::~GeneralSurface()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glDeleteBuffers(BUFFER_COUNT, buffers);
    glDeleteVertexArrays(1, &vao);
}

void GeneralSurface::initializeSurface(int parts)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    
    float deltaU = (u_max - u_min) / N;
    float deltaV = (v_max - v_min) / M;
    
    for (int part = 0; part < parts; ++part) {
        for (float u = u_min; u < (u_max - deltaU); u += deltaU) {
            for (float v = v_min; v < (v_max - deltaV); v += deltaV) {
                glm::vec3 P1 = vertexAt(part, u, v);
                glm::vec3 P2 = vertexAt(part, u + deltaU, v);
                glm::vec3 P3 = vertexAt(part, u + deltaU, v + deltaV);
                glm::vec3 P4 = vertexAt(part, u, v + deltaV);

                glm::vec3 N1 = normalAt(part, u, v);
                glm::vec3 N2 = normalAt(part, u + deltaU, v);
                glm::vec3 N3 = normalAt(part, u + deltaU, v + deltaV);
                glm::vec3 N4 = normalAt(part, u, v + deltaV);

                vertices.push_back(P1);
                vertices.push_back(P2);
                vertices.push_back(P3);

                vertices.push_back(P1);
                vertices.push_back(P3);
                vertices.push_back(P4);

                normals.push_back(N1);
                normals.push_back(N2);
                normals.push_back(N3);

                normals.push_back(N1);
                normals.push_back(N3);
                normals.push_back(N4);
            }
        }
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(),
            &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(),
            &normals[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    num_vertices = vertices.size();
    vertices.clear();
    normals.clear();
}

void GeneralSurface::render() const
{
    glBindVertexArray(vao);
	
	for (int id = 0; id < BUFFER_COUNT; ++id) {
		glEnableVertexAttribArray(id);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[id]);
		glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glDrawArrays(GL_TRIANGLES, 0, num_vertices);
	
	glBindVertexArray(0);
}

