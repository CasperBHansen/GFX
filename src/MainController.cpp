/*
 * Introduction to Computer Graphics
 *
 * MainController.cpp
 *
 */

#include "MainController.h"

#include <iostream>
using std::cout;
using std::endl;

GLfloat triangle[9] =
{
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f
};

#define MOVE_SPEED 0.1f
#define ROTATE_SPEED 0.01f

MainController::MainController()
{
    memset(keys, 0, sizeof(keys));
    
    camera = new Camera();
    cube = new Cube();
    
    shader = new Shader();
    vbo = new VertexBufferObject(GL_TRIANGLES, triangle, sizeof(triangle), 3);
}

MainController::~MainController()
{
	delete cube;
    delete camera;
}

void MainController::init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void MainController::update()
{
    if (keys[W_KEY]) {
        camera->translate(glm::vec3(0,0,1) * MOVE_SPEED);
    }
    
    if (keys[S_KEY]) {
        camera->translate(glm::vec3(0,0,-1) * MOVE_SPEED);
    }
    
    if (keys[A_KEY]) {
        camera->translate(glm::vec3(1,0,0) * MOVE_SPEED);
    }
    
    if (keys[D_KEY]) {
        camera->translate(glm::vec3(-1,0,0) * MOVE_SPEED);
    }
    
    if (keys[UP_KEY]) {
        cube->rotate(glm::vec3(-1,0,0) * ROTATE_SPEED);
    }
    
    if (keys[DOWN_KEY]) {
        cube->rotate(glm::vec3(1,0,0) * ROTATE_SPEED);
    }
    
    if (keys[LEFT_KEY]) {
        cube->rotate(glm::vec3(0,1,0) * ROTATE_SPEED);
    }
    
    if (keys[RIGHT_KEY]) {
        cube->rotate(glm::vec3(0,-1,0) * ROTATE_SPEED);
    }
}

void MainController::render()
{
    glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 mvp = projection * camera->getTranform() * cube->getTranform();
     
    shader->use();
    shader->uniformMatrix4fv("mvp", glm::value_ptr(mvp));
    shader->uniform("color", 1.0f, 0.0f, 0.0f);
    vbo->render(shader->getAttribLocation("vtx"));
    
    glutPostRedisplay();
}
    
void MainController::keyPress(unsigned char key, int x, int y)
{
    switch (key) {
    
        case 27:
            glutLeaveMainLoop();
            break;
        
        case 'w':
            keys[W_KEY] = true;
            break;
        
        case 's':
            keys[S_KEY] = true;
            break;
        
        case 'a':
            keys[A_KEY] = true;
            break;
        
        case 'd':
            keys[D_KEY] = true;
            break;
    }
}

void MainController::keyPress(int key, int x, int y)
{
    switch (key) {
        
        case GLUT_KEY_UP:
            keys[UP_KEY] = true;
            break;
        
        case GLUT_KEY_DOWN:
            keys[DOWN_KEY] = true;
            break;
        
        case GLUT_KEY_LEFT:
            keys[LEFT_KEY] = true;
            break;
        
        case GLUT_KEY_RIGHT:
            keys[RIGHT_KEY] = true;
            break;
    }
}

void MainController::keyRelease(unsigned char key, int x, int y)
{
    switch (key) {
        
        case 'w':
            keys[W_KEY] = false;
            break;
        
        case 's':
            keys[S_KEY] = false;
            break;
        
        case 'a':
            keys[A_KEY] = false;
            break;
        
        case 'd':
            keys[D_KEY] = false;
            break;
    }
}

void MainController::keyRelease(int key, int x, int y)
{
    switch (key) {
        
        case GLUT_KEY_UP:
            keys[UP_KEY] = false;
            break;
        
        case GLUT_KEY_DOWN:
            keys[DOWN_KEY] = false;
            break;
        
        case GLUT_KEY_LEFT:
            keys[LEFT_KEY] = false;
            break;
        
        case GLUT_KEY_RIGHT:
            keys[RIGHT_KEY] = false;
            break;
    }
}
