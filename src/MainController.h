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
#include <vector>

#include "Camera.h"
#include "Shader.h"
#include "BezierPatchModel.h"
#include "DiniSurface.h"
#include "KleinBottle.h"

#define NUM_KEYS 12
typedef enum {
    ENTER_KEY,
    SPACE_KEY,
    UP_KEY,
    DOWN_KEY,
    LEFT_KEY,
    RIGHT_KEY,
    A_KEY,
    D_KEY,
    S_KEY,
    W_KEY,
    PLUS_KEY,
    MINUS_KEY
} Key;

#define KEY_STATE_DEPRESSED true
#define KEY_STATE_RELEASED  false
typedef bool KeyState;

#define DEMO_COUNT 2
typedef enum {
    DEMO_MODELS,
    DEMO_SURFACES
} DemoId;

#define MODEL_COUNT 4
typedef enum {
    MODEL_TEAPOT,
    MODEL_PAIN,
    MODEL_ROCKET,
    MODEL_PATCHES
} ModelId;

#define SURFACE_COUNT 2
typedef enum {
    SURFACE_DINI,
    SURFACE_KLEIN_BOTTLE
} SurfaceId;

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
    int model, surface;
    int demo;
    
    Camera * camera;
    Shader * shader;
    BezierPatchModel * models[MODEL_COUNT];
    GeneralSurface * surfaces[SURFACE_COUNT];
    
    bool keys[NUM_KEYS];
};

#endif // MAINCONTROLLER_H

