/*
 * Introduction to Computer Graphics
 *
 * ProgramGeometricTransformations.cpp
 *
 */

#include "ProgramGeometricTransformations.h"

#include <iostream>
using std::cout;
using std::endl;

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLchar * vertShader = "                                               \n\
#version 110                                                                \n\
                                                                            \n\
attribute vec3 vtx;                                                         \n\
                                                                            \n\
uniform float uScale;                                                       \n\
uniform mat4 uModelMtx;                                                     \n\
                                                                            \n\
void main() {                                                               \n\
    gl_Position = uModelMtx * vec4(uScale * vtx.xy, uScale * vtx.z, 1.0);   \n\
}";

const GLchar * fragShader = "                                               \n\
#version 110                                                                \n\
                                                                            \n\
uniform vec3 uColor;                                                        \n\
void main() {                                                               \n\
    gl_FragColor = vec4(uColor, 1.0);                                       \n\
}";

GLfloat vertices[9] = {
    -1.0f, -1.0f,  0.0f,
     1.0f, -1.0f,  0.0f,
     0.0f,  1.0f,  0.0f
};

ProgramGeometricTransformations::ProgramGeometricTransformations()
                               : ProgramTemplate("Geometric Transformations")
{
    shader = new Shader(vertShader, fragShader); 
    vbo = new VertexBufferObject(GL_TRIANGLES, vertices, 3, shader);
    
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

ProgramGeometricTransformations::~ProgramGeometricTransformations()
{
    delete vbo;
    delete shader;
}

void ProgramGeometricTransformations::init()
{
}

void ProgramGeometricTransformations::update(unsigned char key, int x, int y)
{
    ProgramTemplate::update(key, x, y);
    
    if ( (unsigned int)key == 13 )
        glutPostRedisplay();
}

void ProgramGeometricTransformations::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    shader->use();
    
    glm::mat4 modelMatrix;
    glUniformMatrix4fv(shader->getUniformLocation("uModelMtx"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    
    glUniform1f(shader->getUniformLocation("uScale"), 0.75f);
    glUniform3f(shader->getUniformLocation("uColor"), 0.0f, 1.0f, 0.0f);
    vbo->draw();
/*
    glUniform1f(shader->getUniformLocation("uScale"), 0.5f);
    glUniform3f(shader->getUniformLocation("uColor"), 1.0f, 0.0f, 0.0f);
    vbo->draw();
*/
    glutSwapBuffers();
}

