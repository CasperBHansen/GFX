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
#include "Cube.h"
#include "Shader.h"
#include "VertexBufferObject.h"

#define NUM_KEYS 8

typedef enum {
    UP_KEY,
    DOWN_KEY,
    LEFT_KEY,
    RIGHT_KEY,
    W_KEY,
    A_KEY,
    S_KEY,
    D_KEY
}Key;

class MainController
{
public:
	MainController();
	~MainController();
    
    void init();
    void update();
    void render();
    
    void keyPress(unsigned char key, int x, int y);
    void keyPress(int key, int x, int y);
    void keyRelease(unsigned char key, int x, int y);
    void keyRelease(int key, int x, int y);

protected:
private:
    Camera * camera;
    Cube * cube;
    
    Shader * shader;
    VertexBufferObject * vbo;
    
    bool keys[NUM_KEYS];
};

#endif // MAINCONTROLLER_H

