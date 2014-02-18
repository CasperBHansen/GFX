/*
 * main.cpp
 *
 * The main program file.
 */

#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "programs/ProgramGeometricTransformations.h"

#define PROGRAM ProgramGeometricTransformations

PROGRAM * program;

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 480

static void render_callback()
{
    program->render();
}

static void kbd_callback(unsigned char key, int x, int y)
{
    program->update(key, x, y);
}

int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Introduction to Computer Graphics");
    glutDisplayFunc(&render_callback);
    glutKeyboardFunc(&kbd_callback);

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        std::cerr << "Error: '" << glewGetErrorString(res) << '\'' << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    
    program = new PROGRAM;
    program->init();

    glutMainLoop();
    
    delete program;
    
    return EXIT_SUCCESS;
}


