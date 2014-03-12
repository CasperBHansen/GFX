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
    
    virtual glm::mat4 getTransform();
    
    glm::mat4 getParallelTransform();
    glm::mat4 getPerspectiveTransform();
    
    glm::vec2 getWindowCenter();
    glm::vec2 getViewport();
    glm::vec3 getDirectionOfProjection();

protected:
private:
    static Camera * active;
    
    glm::vec3 vrp; // view reference point
    glm::vec3 vpn; // view plane normal
    glm::vec3 vup; // view up vector
    glm::vec3 prp; // projection reference point
    
    glm::vec2 min; // lower-left
    glm::vec2 max; // upper-right
    
    float near, far; // clipping planes
};

#endif // CAMERA_H

