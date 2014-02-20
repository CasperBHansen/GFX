/*
 * Introduction to Computer Graphics
 *
 * Camera.h
 *
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"

class Camera : public Object
{
public:
	Camera(const glm::vec3 &position = glm::vec3(0,0,0));
	virtual ~Camera();
    
    static Camera * getActiveCamera();
    static void setActiveCamera(Camera * camera);

protected:
private:
    static Camera * active;
};

#endif // CAMERA_H

