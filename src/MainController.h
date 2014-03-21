/*
 * Introduction to Computer Graphics
 *
 * MainController.h
 *
 */

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Camera.h"
#include "Shader.h"
// #include "Mesh.h"
#include "BezierPatchModel.h"

// tests
#include "TestRead.h"
#include "TestBezierPatch.h"

#define NUM_KEYS 10

typedef bool KeyState;

#define KEY_STATE_DEPRESSED true
#define KEY_STATE_RELEASED  false

typedef enum {
    ENTER_KEY,
    SPACE_KEY,
    UP_KEY,
    DOWN_KEY,
    LEFT_KEY,
    RIGHT_KEY,
    W_KEY,
    A_KEY,
    S_KEY,
    D_KEY,
    PLUS_KEY,
    MINUS_KEY
} Key;

#include <vector>

#define MODEL_COUNT 4
typedef enum {
    MODEL_TEAPOT,
    MODEL_PAIN,
    MODEL_ROCKET,
    MODEL_PATCHES
} ModelId;

class MainController
{
public:
	MainController(int width, int height);
	~MainController();
    
    void init();
    void update();
    void render();
    
    void onMouse(int button, int state, int x, int y);
    
    void onKeyboard(KeyState state, unsigned char key, int x, int y);
    void onKeyboard(KeyState state, int key, int x, int y);
    
    void onResize(int width, int height);

protected:
private:
    int width, height;
    int model;
    
    Camera * camera;
    Shader * shader;
    BezierPatchModel * models[MODEL_COUNT];
    
    bool keys[NUM_KEYS];
};

#endif // MAINCONTROLLER_H

