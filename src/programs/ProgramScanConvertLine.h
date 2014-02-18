/*
 * Introduction to Computer Graphics
 *
 * ProgramScanConvertLine.h
 *
 */

#ifndef PROGRAMSCANCONVERTLINE_H
#define PROGRAMSCANCONVERTLINE_H

#include "../ProgramTemplate.h"

#include "../Line.h"

class ProgramScanConvertLine : public ProgramTemplate
{
public:
	ProgramScanConvertLine();
	virtual ~ProgramScanConvertLine();
    
    virtual void init();
    
    virtual void update(unsigned char key, int x, int y);
    virtual void render();

protected:
    void generateLine();

private:
    Point2D a, b;
    Line * line;
};

#endif // PROGRAMSCANCONVERTLINE_H

