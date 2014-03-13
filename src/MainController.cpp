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

MainController::MainController(int width, int height)
{
    this->width  = width;
    this->height = height;
    
    memset(keys, KEY_STATE_RELEASED, sizeof(keys));
    
    count = 0;
/*
    camera = new Camera(glm::vec3(0,0,-50.0));
    shader = new Shader("resources/shaders/phong.shader");
    object = new Mesh("resources/meshes/teapot.obj");
 */
}

MainController::~MainController()
{
    curves.clear();
/*
	delete object;
    delete camera;
    delete shader;
 */
}

void MainController::init()
{
/*
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
 */

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPointSize(4.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluOrtho2D(0.0, width, 0.0, height);
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
/*
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
 */
    
    // draw curves
    for (std::vector<BezierVec4>::iterator it = curves.begin();
         it != curves.end(); ++it)
    {
        (* it).draw(STYLE_SUBDIVISION, 10);
    }
    
    // draw dots
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < count; ++i)
    {
        glBegin(GL_POINTS);
            glVertex2i( points[i].x, points[i].y );
        glEnd();
    }
    
    // draw lines
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for (int i = 0; i < (count - 1); ++i)
    {
        glVertex2i( points[i].x, points[i].y );
        glVertex2i( points[i+1].x, points[i+1].y );
    }
    glEnd();

    glFlush();
}

void MainController::onMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Point p;
        p.x = x;
        p.y = height - y;
        
        points[count] = p;
        count = (count + 1) % 4;
        
        if (count == 0) {
            glm::vec3 param1(points[0].x, points[0].y, 0.0);
            glm::vec3 param2(points[1].x, points[1].y, 0.0);
            glm::vec3 param3(points[2].x, points[2].y, 0.0);
            glm::vec3 param4(points[3].x, points[3].y, 0.0);
            
            curves.push_back(BezierVec4(param1, param2, param3, param4));
        }
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
