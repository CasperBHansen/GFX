/*
 * Introduction to Computer Graphics
 *
 * KleinBottle.h
 *
 */

#ifndef KLEINBOTTLE_H
#define KLEINBOTTLE_H

#include "GeneralSurface.h"

class KleinBottle : public GeneralSurface
{
public:
	KleinBottle(int N, int M);
	~KleinBottle();

protected:
    glm::vec3 vertexAt(int part, float u, float v);
    glm::vec3 normalAt(int part, float u, float v);
    
private:
};

#endif // KLEINBOTTLE_H

