/*
 * Introduction to Computer Graphics
 *
 * MainController.cpp
 *
 */

#include "MainController.h"

#define release(ptr) if (ptr) { delete ptr; ptr = NULL; }

#include <iostream>
using std::cout;
using std::endl;

#define MOVE_SPEED 0.5f
#define ROTATE_SPEED 0.1f

MainController::MainController(int width, int height)
{
    this->width  = width;
    this->height = height;
    
    memset(keys, KEY_STATE_RELEASED, sizeof(keys));
    
    model = MODEL_TEAPOT;
    
    camera = new Camera(glm::vec3(0.0f, -1.0f, -10.0f));
    shader = new Shader("resources/shaders/phong.shader");
    
    models[MODEL_TEAPOT]  = new BezierPatchModel("resources/data/teapot.data");
    models[MODEL_PAIN]    = new BezierPatchModel("resources/data/pain.data");
    models[MODEL_ROCKET]  = new BezierPatchModel("resources/data/rocket.data");
    models[MODEL_PATCHES] = new BezierPatchModel("resources/data/patches.data");
}

MainController::~MainController()
{
    for (int i = 0; i < MODEL_COUNT; ++i)
        release(models[i]);

	release(camera);
    release(shader);
}

void MainController::init()
{
    glViewport(0, 0, width, height);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    
    if (keys[SPACE_KEY])    model = (model + 1) % 4;
    if (keys[PLUS_KEY])     models[model]->increaseLevel();
    if (keys[MINUS_KEY])    models[model]->decreaseLevel();
}

void MainController::render()
{
    static unsigned long frame = 0;
    static float time = 0.0f;
    
    glm::mat4 mv  = Camera::getActiveCamera()->getTransform() * models[model]->getTransform();
    glm::mat4 mvp = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f) * mv;
    
    shader->use();
    shader->uniform("mv",  mv);
    shader->uniform("mvp", mvp);
    shader->uniform("eye", Camera::getActiveCamera()->getPosition());
    
    shader->uniform("Ai", 0.25f, 0.25f, 0.25f);
    
    shader->uniform("Li", 0.5f, 0.5f, 0.5f);
    shader->uniform("Lp", 10 * sin(time), 10 * cos(time), 0.0f);
    
    shader->uniform("Ka", 0.38f);
    shader->uniform("Kd", 0.68f);
    shader->uniform("Ks", 0.81f);
    
    shader->uniform("Oa", 0.0f, 1.0f, 0.0f);
    shader->uniform("Od", 0.0f, 1.0f, 0.0f);
    shader->uniform("Os", 1.0f, 1.0f, 1.0f);
    
    shader->uniform("Fatt", 1.0f);
    shader->uniform("n", 20.0f);

    models[model]->render();
    
    time += 0.1f;
    frame += 1;
}

void MainController::onMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
    }
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
        
        case 'p':
            keys[PLUS_KEY] = state;
            break;
        
        case 'm':
            keys[MINUS_KEY] = state;
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

void MainController::onResize(int width, int height)
{
    this->width  = width;
    this->height = height;
    this->init();
}
