/*
 * Line.h
 *
 * Definition of the line primtive.
 */

#ifndef LINE_H
#define LINE_H

#include "Types.h"
#include "utilities/Drawer.h"

class Line
{
public:
    Line(Point2D a, Point2D b);
    ~Line();
    
    void draw(Drawer * draw) const;
    
    Vector2D getNormal() const;
    float getSlope() const;
    
    void setPoints(const Point2D &a, const Point2D &b);
    void setPointA(const Point2D &point);
    void setPointB(const Point2D &point);

protected:
    
private:
    Point2D a, b;
};

#endif // LINE_H

