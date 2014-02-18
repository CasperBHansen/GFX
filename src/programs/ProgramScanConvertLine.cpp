/*
 * Introduction to Computer Graphics
 *
 * ProgramScanConvertLine.cpp
 *
 */

#include "ProgramScanConvertLine.h"

#include <iostream>
using std::cout;
using std::endl;

#define RAND_RANGE(min, max) (int)( (max - min) * ( (float)rand() / (float)RAND_MAX ) + min )

ProgramScanConvertLine::ProgramScanConvertLine()
                      : ProgramTemplate("Scan-convert Line")
{
    line = new Line(a, b);
}

ProgramScanConvertLine::~ProgramScanConvertLine()
{
    delete line;
}

void ProgramScanConvertLine::init()
{
    generateLine();
}

void ProgramScanConvertLine::update(unsigned char key, int x, int y)
{
    ProgramTemplate::update(key, x, y);
    
    if ( (unsigned int)key == 13 )
        generateLine();
}

void ProgramScanConvertLine::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor4f(0.38f, 0.38f, 0.38f, 1.0f);
	draw.grid();
    
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    line->draw(&draw);
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	draw.line(a, b);
    
    glutSwapBuffers();
}

void ProgramScanConvertLine::generateLine()
{
    a.x = RAND_RANGE(-5, 5);
    a.y = RAND_RANGE(-5, 5);
    b.x = RAND_RANGE(-5, 5);
    b.y = RAND_RANGE(-5, 5);
    
    line->setPointA(a);
    line->setPointB(b);
    
    cout << "Generated a new line" << endl;    
    cout << "a: " << a << endl;
    cout << "b: " << b << endl << endl;
    
    glutPostRedisplay();
}

