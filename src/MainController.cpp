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

#define MOVE_SPEED 0.5f
#define ROTATE_SPEED 0.5f

MainController::MainController()
{
    memset(keys, KEY_STATE_RELEASED, sizeof(keys));
    
    camera = new Camera(glm::vec3(0,0,-5.0));
    house = new House();
    shader = new Shader();
}

MainController::~MainController()
{
	delete house;
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
    if (keys[W_KEY])        camera->translate(glm::vec3(0,0,1) * MOVE_SPEED);
    if (keys[S_KEY])        camera->translate(glm::vec3(0,0,-1) * MOVE_SPEED);
    if (keys[A_KEY])        camera->translate(glm::vec3(1,0,0) * MOVE_SPEED);
    if (keys[D_KEY])        camera->translate(glm::vec3(-1,0,0) * MOVE_SPEED);
    
    if (keys[UP_KEY])       camera->rotate(glm::vec3(-1,0,0) * ROTATE_SPEED);
    if (keys[DOWN_KEY])     camera->rotate(glm::vec3(1,0,0) * ROTATE_SPEED); 
    if (keys[LEFT_KEY])     camera->rotate(glm::vec3(0,1,0) * ROTATE_SPEED);
    if (keys[RIGHT_KEY])    camera->rotate(glm::vec3(0,-1,0) * ROTATE_SPEED);
}

void MainController::render()
{
    house->render(shader);
}
    
void MainController::onKeyboard(KeyState state, unsigned char key, int x, int y)
{
    switch (key) {
    
        case 27:
            glutLeaveMainLoop();
            break;
    
        case 13:
            keys[ENTER_KEY] = state;
            break;
    
        case ' ':
            keys[SPACE_KEY] = state;
            break;
        
        case 'w':
            keys[W_KEY] = state;
            break;
        
        case 's':
            keys[S_KEY] = state;
            break;
        
        case 'a':
            keys[A_KEY] = state;
            break;
        
        case 'd':
            keys[D_KEY] = state;
            break;
    }
}

void MainController::onKeyboard(KeyState state, int key, int x, int y)
{
    switch (key) {
        
        case GLUT_KEY_UP:
            keys[UP_KEY] = state;
            break;
        
        case GLUT_KEY_DOWN:
            keys[DOWN_KEY] = state;
            break;
        
        case GLUT_KEY_LEFT:
            keys[LEFT_KEY] = state;
            break;
        
        case GLUT_KEY_RIGHT:
            keys[RIGHT_KEY] = state;
            break;
    }
}

