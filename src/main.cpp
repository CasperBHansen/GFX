/*
 * main.cpp
 *
 * The main program file.
 */

#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "MainController.h"

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 480

MainController * program;

static void render_callback()
{
    program->update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program->render();
    glutSwapBuffers();
}

static void kbd_down_callback(unsigned char key, int x, int y)
{
    program->keyPress(key, x, y);
}

static void kbd_up_callback(unsigned char key, int x, int y)
{
    program->keyRelease(key, x, y);
}

static void kbd_special_down_callback(int key, int x, int y)
{
    program->keyPress(key, x, y);
}

static void kbd_special_up_callback(int key, int x, int y)
{
    program->keyRelease(key, x, y);
}

int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Introduction to Computer Graphics");
    glutDisplayFunc(&render_callback);
    glutKeyboardFunc(&kbd_down_callback);
    glutKeyboardUpFunc(&kbd_up_callback);
    glutSpecialFunc(&kbd_special_down_callback);
    glutSpecialUpFunc(&kbd_special_up_callback);

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        std::cerr << "Error: '" << glewGetErrorString(res) << '\'' << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    
    program = new MainController;
    program->init();

    glutMainLoop();
    
    delete program;
    
    return EXIT_SUCCESS;
}


