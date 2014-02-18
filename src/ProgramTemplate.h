/*
 * ProgramTemplate.h
 *
 * Declares the program template class, which is an abstract class that serves
 * to make it easier to write several test programs omitting redundant rewrite
 * of windowing setup etc.
 */

#ifndef PROGRAMTEMPLATE_H
#define PROGRAMTEMPLATE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "utilities/Drawer.h"

class ProgramTemplate
{
public:
    ProgramTemplate(const char * title);
    virtual ~ProgramTemplate();
    
    virtual void init() = 0;
    
    virtual void update(unsigned char key, int x, int y);
    virtual void render() = 0;

protected:
    Drawer draw;
    
private:
};

#endif // PROGRAMTEMPLATE_H

