/*
 * Introduction to Computer Graphics
 *
 * Drawer.h
 *
 */

#ifndef DRAWER_H
#define DRAWER_H

#include "GLFilledCircle.h"
#include "GLLineGrid.h"
#include "GLLine.h"

#include "../Types.h"

class Drawer
{
public:
	Drawer();
	~Drawer();
    
    void grid();
    void point(const Point2D &point);
    void point(int x, int y);
    void line(const Point2D &a, const Point2D &b);

protected:
private:
    bool hardwareShaderSupport;
    float gridCellSize;
    
    GLFilledCircle p;
    GLLineGrid g;
    GLLine l;
};

#endif // DRAWER_H

