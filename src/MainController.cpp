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
    
    demo    = DEMO_MODELS;
    model   = MODEL_TEAPOT;
    surface = SURFACE_DINI;
    mask    = SURFACE;
    
    camera  = new Camera(glm::vec3(0.0f, -2.0f, -10.0f),
                         glm::vec3(0.0f, 0.0f, 0.0f));
    phong   = new Shader("resources/shaders/phong.shader");
    twoside = new Shader("resources/shaders/two-sided-phong.shader");
    
    models[MODEL_TEAPOT]  = new BezierPatchModel("resources/data/teapot.data");
    models[MODEL_PAIN]    = new BezierPatchModel("resources/data/pain.data");
    models[MODEL_ROCKET]  = new BezierPatchModel("resources/data/rocket.data");
    models[MODEL_PATCHES] = new BezierPatchModel("resources/data/patches.data");
    
    int N = 64;
    surfaces[SURFACE_DINI]          = new DiniSurface(N, N, 0.5f, 0.2f);
    surfaces[SURFACE_KLEIN_BOTTLE]  = new KleinBottle(N, N);
}

MainController::~MainController()
{
    for (int i = 0; i < MODEL_COUNT; ++i)
        release(models[i]);
    
    for (int i = 0; i < SURFACE_COUNT; ++i)
        release(surfaces[i]);

    release(phong);
    release(twoside);
    
	release(camera);
}

void MainController::init()
{
    glViewport(0, 0, width, height);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
/*
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
 */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void MainController::update()
{
    static int last_time = glutGet(GLUT_ELAPSED_TIME);
    static int curr_time = 0;
    
    curr_time = glutGet(GLUT_ELAPSED_TIME);
    
    if (keys[W_KEY])        camera->translate(glm::vec3(0,0,1) * MOVE_SPEED);
    if (keys[S_KEY])        camera->translate(glm::vec3(0,0,-1) * MOVE_SPEED);
    if (keys[A_KEY])        camera->translate(glm::vec3(1,0,0) * MOVE_SPEED);
    if (keys[D_KEY])        camera->translate(glm::vec3(-1,0,0) * MOVE_SPEED);
    
    if (keys[UP_KEY])       camera->rotate(glm::vec3(-1,0,0) * ROTATE_SPEED);
    if (keys[DOWN_KEY])     camera->rotate(glm::vec3(1,0,0) * ROTATE_SPEED); 
    if (keys[LEFT_KEY])     camera->rotate(glm::vec3(0,1,0) * ROTATE_SPEED);
    if (keys[RIGHT_KEY])    camera->rotate(glm::vec3(0,-1,0) * ROTATE_SPEED);
    
    // don't react so quickly for these keys
    if ( (curr_time - last_time) < 60 )
        return;
    
    if (keys[NUM_1_KEY])    mask = POINTS;
    if (keys[NUM_2_KEY])    mask = LINES;
    if (keys[NUM_3_KEY])    mask = SURFACE;
    
    if (keys[ENTER_KEY])    demo = (demo + 1) % SURFACE_COUNT;
    if (keys[SPACE_KEY])    {
                                model   = (model + 1) % MODEL_COUNT;
                                surface = (surface + 1) % SURFACE_COUNT;
                            }
    if (keys[PLUS_KEY])     models[model]->increaseLevel();
    if (keys[MINUS_KEY])    models[model]->decreaseLevel();
    
    last_time = curr_time;
}

void MainController::render()
{
    static unsigned long frame = 0;
    static float time = 0.0f;
    static Shader * shader = NULL;
    
    glm::mat4 mv  = Camera::getActiveCamera()->getTransform() * models[model]->getTransform();
    glm::mat4 mvp = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f) * mv;
    
    if (demo == DEMO_SURFACES && surface == SURFACE_DINI) Shader::use(twoside);
    else Shader::use(phong);
    
    shader = Shader::getActiveShader();
    shader->uniform("mv",  mv);
    shader->uniform("mvp", mvp);
    shader->uniform("eye", Camera::getActiveCamera()->getPosition());
    
    shader->uniform("Ai", 0.5f, 0.5f, 0.5f);
    
    shader->uniform("Li", 0.62f, 0.62f, 0.62f);
    shader->uniform("Lp", 5.0f * sinf(time), 5.0f, 5.0f * sinf(time + (M_PI / 2.0f)));
    
    shader->uniform("Ka", 0.38f);
    shader->uniform("Kd", 0.68f);
    shader->uniform("Ks", 0.92f);
    
    shader->uniform("Oa", 0.5f, 0.04f, 0.29f);
    shader->uniform("Od", 1.0f, 0.08f, 0.58f);
    shader->uniform("Os", 1.0f, 1.0f, 1.0f);
    
    shader->uniform("Fatt", 1.0f);
    shader->uniform("n", 50.0f);

    switch (demo)
    {
        case DEMO_MODELS:
            models[model]->render(mask);
            break;
        
        case DEMO_SURFACES:
            surfaces[surface]->render(mask);
            break;
    }
    
    time += 0.05f;
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
    
        case '1':
            keys[NUM_1_KEY] = state;
            break;
    
        case '2':
            keys[NUM_2_KEY] = state;
            break;
    
        case '3':
            keys[NUM_3_KEY] = state;
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
        
        case '+':
            keys[PLUS_KEY] = state;
            break;
        
        case '-':
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
