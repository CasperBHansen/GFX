/*
 * Introduction to Computer Graphics
 *
 * Drawer.cpp
 *
 */

#include "Drawer.h"

Drawer::Drawer()
{
	hardwareShaderSupport = GLEW_VERSION_3_0;
    gridCellSize = 0.10f;
 	
    p.initializeBuffers(hardwareShaderSupport, gridCellSize * 0.5f);
	g.initializeBuffers(hardwareShaderSupport, gridCellSize);
	l.initializeBuffers(hardwareShaderSupport, gridCellSize);
}

Drawer::~Drawer()
{
	// destructor
}

void Drawer::grid()
{
    g.draw();
}

void Drawer::point(const Point2D &point)
{
    p.draw(point.x, point.y);
}

void Drawer::point(int x, int y)
{
    p.draw(x, y);
}

void Drawer::line(const Point2D &a, const Point2D &b)
{
    l.draw(a.x, a.y, b.x, b.y);
}

