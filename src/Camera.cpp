/*
 * Introduction to Computer Graphics
 *
 * Camera.cpp
 *
 */

#include "Camera.h"

#include <iostream>

#include <math.h>
#include <glm/geometric.hpp>

Camera * Camera::active = NULL;

Camera::Camera(const glm::vec3 &position,
               const glm::vec3 &rotation)
      : Object(position, rotation)
{
    vrp = glm::vec3(0.0, 0.0, 0.0);
    vpn = glm::vec3(0.0, 0.0, 1.0);
    vup = glm::vec3(0.0, 1.0, 0.0);
    prp = glm::vec3(0.0, 0.0, 100.0);
    
    near =  0.1f;
    far  = -200.0f;
    
    min = glm::vec2(-25.0f, -25.0f);
    max = glm::vec2( 25.0f,  25.0f);
    
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

glm::mat4 Camera::getTransform()
{
    float s[16] =
    {
        _scale.x,   0.0f,       0.0f,       0.0f,
        0.0f,       _scale.y,   0.0f,       0.0f,
        0.0f,       0.0f,       _scale.z,   0.0f,
        0.0f,       0.0f,       0.0f,       1.0f
    };
    
    float r_x[16] =
    {
        1.0f,   0.0f,                   0.0f,                   0.0f,
        0.0f,   glm::cos(_rotation.x),  glm::sin(_rotation.x),  0.0f,
        0.0f,  -glm::sin(_rotation.x),  glm::cos(_rotation.x),  0.0f,
        0.0f,   0.0f,                   0.0f,                   1.0f
    };
    
    float r_y[16] =
    {
        glm::cos(_rotation.y),  0.0f,  -glm::sin(_rotation.y),  0.0f,
        0.0f,                   1.0f,   0.0f,                   0.0f,
        glm::sin(_rotation.y),  0.0f,   glm::cos(_rotation.y),  0.0f,
        0.0f,                   0.0f,   0.0f,                   1.0f
    };
    
    float r_z[16] =
    {
        glm::cos(_rotation.z),  glm::sin(_rotation.z),  0.0f,   0.0f,
       -glm::sin(_rotation.z),  glm::cos(_rotation.z),  0.0f,   0.0f,
        0.0f,                   0.0f,                   1.0f,   0.0f,
        0.0f,                   0.0f,                   0.0f,   1.0f
    };
    
    float t[16] =
    {
        1.0f,           0.0f,           0.0f,           0.0f,
        0.0f,           1.0f,           0.0f,           0.0f,
        0.0f,           0.0f,           1.0f,           0.0f,
        _position.x,    _position.y,    _position.z,    1.0f
    };
    
    glm::mat4 s_mtx = glm::make_mat4(s);
    glm::mat4 r_mtx = glm::make_mat4(r_z) * glm::make_mat4(r_y) * glm::make_mat4(r_x);
    glm::mat4 t_mtx = glm::make_mat4(t);
    
    matrix = t_mtx * r_mtx * s_mtx;
    
    return matrix;
}

glm::mat4 Camera::getParallelTransform()
{
    // translation
    glm::mat4 T_vrp({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        -vrp.x, -vrp.y, -vrp.z, 1.0f
    });
    
    // z-rotation
    float l = glm::length(vpn);
    glm::vec3 rz = vpn / l;
    
    // x-rotation
    glm::vec3 vup_x_rz = glm::cross(vup, rz);
    l = glm::length(vup_x_rz);
    glm::vec3 rx = vup_x_rz / l;
    
    // y-rotation
    glm::vec3 rz_x_rx = glm::cross(rz, rx);
    l = glm::length(rz_x_rx);
    glm::vec3 ry = rz_x_rx / l;
    
    // rotation
    glm::mat4 R({
        rx.x, ry.x, rz.x, 0.0f,
        rx.y, ry.y, rz.y, 0.0f,
        rx.z, ry.z, rz.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    // shear - Sh
    glm::vec3 dop = getDirectionOfProjection();
    float sh_x = -(dop.x / dop.z);
    float sh_y = -(dop.y / dop.z);
    glm::mat4 Sh({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sh_x, sh_y, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    // translate
    glm::vec2 cw = getWindowCenter();
    glm::mat4 T_par({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        -cw.x, -cw.y, -near, 1.0f
    });
    
    // scale
    glm::mat4 S_par({
        2.0f / (max.x - min.x), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (max.y - min.y), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f / (near - far), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    return S_par * T_par * Sh * R * T_vrp * Object::getTransform();
}

glm::mat4 Camera::getPerspectiveTransform()
{
    // translation - T(-VRP)
    glm::mat4 T_vrp({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        -vrp.x, -vrp.y, -vrp.z, 1.0f
    });
    
    // z-rotation
    float l = glm::length(vpn);
    glm::vec3 rz = vpn / l;
    
    // x-rotation
    glm::vec3 vup_x_rz = glm::cross(vup, rz);
    l = glm::length(vup_x_rz);
    glm::vec3 rx = vup_x_rz / l;
    
    // y-rotation
    glm::vec3 rz_x_rx = glm::cross(rz, rx);
    l = glm::length(rz_x_rx);
    glm::vec3 ry = rz_x_rx / l;
    
    // rotation - R
    glm::mat4 R({
        rx.x, ry.x, rz.x, 0.0f,
        rx.y, ry.y, rz.y, 0.0f,
        rx.z, ry.z, rz.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    // translation - T(-PRP)
    glm::mat4 T_prp({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        -prp.x, -prp.y, -prp.z, 1.0f
    });
    
    // shear - Sh
    glm::vec3 dop = getDirectionOfProjection();
    float sh_x = -(dop.x / dop.z);
    float sh_y = -(dop.y / dop.z);
    glm::mat4 Sh({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sh_x, sh_y, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    glm::mat4 S({
        (-2.0f * prp.z) / ( (max.x - min.x) * (far - prp.z)), 0.0f, 0.0f, 0.0f,
        0.0f, (-2.0f * prp.z) / ( (max.y - min.y) * (far - prp.z)), 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f / (far - prp.z), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    });
    
    glm::mat4 P({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 1.0f / (prp.z / (far - prp.z) ),
        0.0f, 0.0f, 0.0f, 0.0f,
    });
    
    return P * S * Sh * T_prp * R * T_vrp * Object::getTransform();
}

glm::vec2 Camera::getWindowCenter()
{
    return glm::vec2( (min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f );
}

glm::vec2 Camera::getViewport()
{
    return glm::vec2( max.x - min.x, max.y - min.y );
}

glm::vec3 Camera::getDirectionOfProjection()
{
    glm::vec2 cw = getWindowCenter();
    return glm::vec3(prp.x - cw.x, prp.y - cw.y, prp.z);
}

