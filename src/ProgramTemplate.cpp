/*
 * ProgramTemplate.cpp
 *
 * Implementation of the program template.
 */

#include <iostream>
using std::cout;
using std::endl;

#include "ProgramTemplate.h"

ProgramTemplate::ProgramTemplate(const char * title)
{
    cout << "Starting program: " << title << endl << endl;
    srand( (unsigned int)time(NULL) );
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    cout << "Usage:" << endl;
    cout << "- ENTER generates a new random object" << endl;
    cout << "- ESC exits the program" << endl << endl;
}

ProgramTemplate::~ProgramTemplate()
{
}

void ProgramTemplate::update(unsigned char key, int x, int y)
{
    if ( (unsigned int)key == 27 ) glutLeaveMainLoop();
}

