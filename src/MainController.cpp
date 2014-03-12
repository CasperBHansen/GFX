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
#define ROTATE_SPEED 0.1f

MainController::MainController()
{
    memset(keys, KEY_STATE_RELEASED, sizeof(keys));
    
    camera = new Camera(glm::vec3(0,0,-50.0));
    shader = new Shader("resources/shaders/phong.shader");
    object = new Mesh("resources/meshes/teapot.obj");
}

MainController::~MainController()
{
	delete object;
    delete camera;
    delete shader;
}

void MainController::init()
{
    cout << "Initializing OpenGL .." << endl;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void MainController::update()
{
    if (keys[W_KEY])        camera->translate(glm::vec3(0,0,1) * MOVE_SPEED);
    if (keys[S_KEY])        camera->translate(glm::vec3(0,0,-1) * MOVE_SPEED);
    if (keys[A_KEY])        camera->translate(glm::vec3(1,0,0) * MOVE_SPEED);
    if (keys[D_KEY])        camera->translate(glm::vec3(-1,0,0) * MOVE_SPEED);
    
    if (keys[UP_KEY])       object->rotate(glm::vec3(-1,0,0) * ROTATE_SPEED);
    if (keys[DOWN_KEY])     object->rotate(glm::vec3(1,0,0) * ROTATE_SPEED); 
    if (keys[LEFT_KEY])     object->rotate(glm::vec3(0,1,0) * ROTATE_SPEED);
    if (keys[RIGHT_KEY])    object->rotate(glm::vec3(0,-1,0) * ROTATE_SPEED);
}

void MainController::render()
{
    static float time = 0.0f;
    
    glm::mat4 m = object->getTransform();
    glm::mat4 v = Camera::getActiveCamera()->getTransform();
    glm::mat4 p = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    
    shader->use();
    shader->uniformMatrix4fv("m", glm::value_ptr(m));
    shader->uniformMatrix4fv("v", glm::value_ptr(v));
    shader->uniformMatrix4fv("p", glm::value_ptr(p));
    
    shader->uniform("Ai", 0.5f, 0.5f, 0.5f);
    
    shader->uniform("Li", 0.5f, 0.5f, 0.5f);
    shader->uniform("Lp", 10 * sin(time), 25.0f, 10 * cos(time));
    
    shader->uniform("Ka", 0.50f);
    shader->uniform("Kd", 0.75f);
    shader->uniform("Ks", 0.90f);
    
    shader->uniform("Oa", 0.0f, 1.0f, 0.0f);
    shader->uniform("Od", 0.0f, 1.0f, 0.0f);
    shader->uniform("Os", 1.0f, 1.0f, 1.0f);
    
    shader->uniform("Fatt", 1.0f);
    shader->uniform("n", 20.0f);

    object->render();
    
    time += 0.05f;
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

