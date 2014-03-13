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
#include "Mesh.h"

#include "BezierVec4.h"

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
    D_KEY
} Key;

struct Point {
    int x, y;
};

#include <vector>

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
    
    Camera * camera;
    Mesh * object;
    
    Shader * shader;
    
    bool keys[NUM_KEYS];
    
    int count;
    Point points[4];
    std::vector<BezierVec4> curves;
};

#endif // MAINCONTROLLER_H

