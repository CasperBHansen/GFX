/*
 * Introduction to Computer Graphics
 *
 * Camera.cpp
 *
 */

#include "Camera.h"

Camera * Camera::active = NULL;

Camera::Camera(const glm::vec3 &position)
      : Object(position)
{
    if (Camera::getActiveCamera() == NULL)
        Camera::setActiveCamera(this);
}

Camera::~Camera()
{
    if (Camera::getActiveCamera() == this)
        Camera::setActiveCamera(NULL);
}

Camera * Camera::getActiveCamera()
{
    return Camera::active;
}

void Camera::setActiveCamera(Camera * camera)
{
    Camera::active = camera;
}

