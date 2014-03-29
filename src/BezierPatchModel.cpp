/*
 * Introduction to Computer Graphics
 *
 * BezierPatchModel.cpp
 *
 */

#include "BezierPatchModel.h"

#include <iostream>

#include "ReadBezierPatches.h"

BezierPatchModel::BezierPatchModel(const char * filename)
{
    try {
        ReadBezierPatches(filename, patches);
        setLevel(1);
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

BezierPatchModel::~BezierPatchModel()
{
    patches.clear();
    vertices.clear();
    normals.clear();
    
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glDeleteBuffers(BUFFER_COUNT, buffers);
	glDeleteVertexArrays(1, &vao);
}

void BezierPatchModel::update()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glDeleteBuffers(BUFFER_COUNT, buffers);
	glDeleteVertexArrays(1, &vao);
    
    for (std::vector<BezierPatch>::const_iterator patch = patches.begin();
            patch != patches.end(); ++patch) {

        subdivide(* patch, level);
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(BUFFER_COUNT, buffers);

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

void BezierPatchModel::subdivide(const BezierPatch &patch, int n)
{
    static glm::mat4x4 M(glm::vec4(-1.0f,  3.0f, -3.0f, 1.0f),
            glm::vec4( 3.0f, -6.0f,  3.0f, 0.0f),
            glm::vec4(-3.0f,  3.0f,  0.0f, 0.0f),
            glm::vec4( 1.0f,  0.0f,  0.0f, 0.0f));

    static glm::mat4x4 DLB = glm::mat4x4(glm::vec4(8.0f, 0.0f, 0.0f, 0.0f),
            glm::vec4(4.0f, 4.0f, 0.0f, 0.0f),
            glm::vec4(2.0f, 4.0f, 2.0f, 0.0f),
            glm::vec4(1.0f, 3.0f, 3.0f, 1.0f)) / 8.0f;

    static glm::mat4x4 DRB = glm::mat4x4(glm::vec4(1.0f, 3.0f, 3.0f, 1.0f),
            glm::vec4(0.0f, 2.0f, 4.0f, 2.0f),
            glm::vec4(0.0f, 0.0f, 4.0f, 4.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 8.0f)) / 8.0f;

    if (n == 0) {
        float s, t;
        glm::vec4 S, T;

        BezierPatch MTGM = (glm::transpose(M) * patch * M);

        s = 0.0f;   t = 0.0f;
        S = glm::vec4(s*s*s, s*s, s, 1.0f);
        T = glm::vec4(t*t*t, t*t, t, 1.0f);
        glm::vec3 P1 = S * MTGM * T;

        s = 1.0f;   t = 0.0f;
        S = glm::vec4(s*s*s, s*s, s, 1.0f);
        T = glm::vec4(t*t*t, t*t, t, 1.0f);
        glm::vec3 P2 = S * MTGM * T;

        s = 1.0f;   t = 1.0f;
        S = glm::vec4(s*s*s, s*s, s, 1.0f);
        T = glm::vec4(t*t*t, t*t, t, 1.0f);
        glm::vec3 P3 = S * MTGM * T;

        s = 0.0f;   t = 1.0f;
        S = glm::vec4(s*s*s, s*s, s, 1.0f);
        T = glm::vec4(t*t*t, t*t, t, 1.0f);
        glm::vec3 P4 = S * MTGM * T;
        
        glm::vec3 N1 = glm::cross(P1-P2, P1-P3);
        glm::vec3 N2 = glm::cross(P1-P3, P1-P4);
    
        glm::vec3 N  = glm::normalize( (N1 + N2) / 2.0f );
        
        normals.push_back(N);
        normals.push_back(N);
        normals.push_back(N);
        
        vertices.push_back(P1);
        vertices.push_back(P3);
        vertices.push_back(P2);
        
        normals.push_back(N);
        normals.push_back(N);
        normals.push_back(N);
        
        vertices.push_back(P1);
        vertices.push_back(P4);
        vertices.push_back(P3);
    }
    else {
        BezierPatch G11 = glm::transpose(DLB) * patch * DLB;
        BezierPatch G12 = glm::transpose(DRB) * patch * DLB;
        BezierPatch G21 = glm::transpose(DLB) * patch * DRB;
        BezierPatch G22 = glm::transpose(DRB) * patch * DRB;

        subdivide(G11, n - 1);
        subdivide(G12, n - 1);
        subdivide(G21, n - 1);
        subdivide(G22, n - 1);
    }
}

void BezierPatchModel::render() const
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

void BezierPatchModel::setLevel(int n)
{
    level = (n >= 0) ? n : 0;
    update();
}

void BezierPatchModel::increaseLevel()
{
    setLevel(level + 1);
}
void BezierPatchModel::decreaseLevel()
{
    setLevel(level - 1);
}

