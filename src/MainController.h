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

class MainController
{
public:
	MainController();
	~MainController();
    
    void init();
    void update();
    void render();
    
    void onKeyboard(KeyState state, unsigned char key, int x, int y);
    void onKeyboard(KeyState state, int key, int x, int y);

protected:
private:
    Camera * camera;
    Mesh * object;
    
    Shader * shader;
    
    bool keys[NUM_KEYS];
};

#endif // MAINCONTROLLER_H

