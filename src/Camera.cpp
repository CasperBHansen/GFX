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

#define NUM_TESTS 5

Camera * Camera::active = NULL;

Camera::Camera(const glm::vec3 &position)
      : Object(position)
{
    test();
    
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
    // todo: make one if none exists
    return Camera::active;
}

void Camera::setActiveCamera(Camera * camera)
{
    Camera::active = camera;
}

glm::mat4 Camera::getTransform()
{
    glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    glm::mat4 view = Object::getTransform();
    return projection * view;
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
    glm::vec3 rz = vpn / (l * l);
    
    // x-rotation
    glm::vec3 vup_x_rz = glm::cross(vup, rz);
    l = glm::length(vup_x_rz);
    glm::vec3 rx = vup_x_rz / (l * l);
    
    // y-rotation
    glm::vec3 rz_x_rx = glm::cross(rz, rx);
    l = glm::length(rz_x_rx);
    glm::vec3 ry = rz_x_rx / (l * l);
    
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
        -cw.x, -cw.y, -front, 1.0f
    });
    
    // scale
    glm::mat4 S_par({
        2.0f / (max.x - min.x), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (max.y - min.y), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f / (front - back), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    glm::mat4 Ortho({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    });
    
    glm::mat4 S_wv({
        (max.x - min.x) / 2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, (max.y - min.y) / 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    });
    
    glm::mat4 T_wv({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
    });
    
    return Ortho * S_par * T_par * Sh * R * T_vrp * Object::getTransform();
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
    glm::vec3 rz = vpn / (l * l);
    
    // x-rotation
    glm::vec3 vup_x_rz = glm::cross(vup, rz);
    l = glm::length(vup_x_rz);
    glm::vec3 rx = vup_x_rz / (l * l);
    
    // y-rotation
    glm::vec3 rz_x_rx = glm::cross(rz, rx);
    l = glm::length(rz_x_rx);
    glm::vec3 ry = rz_x_rx / (l * l);
    
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
        (-2.0f * prp.z) / ( (max.x - min.x) * (back - prp.z)), 0.0f, 0.0f, 0.0f,
        0.0f, (-2.0f * prp.z) / ( (max.y - min.y) * (back - prp.z)), 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f / (back - prp.z), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    });
    
    glm::mat4 P({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 1.0f / (prp.z / (back - prp.z) ),
        0.0f, 0.0f, 0.0f, 0.0f,
    });
    
    glm::mat4 S_wv({
        (max.x - min.x) / 2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, (max.y - min.y) / 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    });
    
    glm::mat4 T_wv({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
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

int Camera::test()
{
    static unsigned int current = NUM_TESTS - 1;
    current = (current + 1) % NUM_TESTS;
    
    std::cout << "Running test " << current + 1 << std::endl;
    switch (current) {
    
        case 0:
            vrp = glm::vec3(0.0f, 0.0f, 0.0f);
            vpn = glm::vec3(0.0f, 0.0f, 1.0f);
            vup = glm::vec3(0.0f, 1.0f, 0.0f);
            prp = glm::vec3(8.0f, 6.0f, 84.0f);
            
            min = glm::vec2(-50.0f,-50.0f);
            max = glm::vec2( 50.0f, 50.0f);
            
            front = 60.0f;
            back  = 25.0f;
            break;
    
        case 1:
            vrp = glm::vec3(0.0f, 0.0f, 54.0f);
            vpn = glm::vec3(0.0f, 0.0f, 1.0f);
            vup = glm::vec3(0.0f, 1.0f, 0.0f);
            prp = glm::vec3(8.0f, 6.0f, 30.0f);
            
            min = glm::vec2(-1.0f,-1.0f);
            max = glm::vec2( 17.0f, 17.0f);
            
            front = 1.0f;
            back  = -35.0f;
            break;
    
        case 2:
            vrp = glm::vec3(16.0f, 0.0f, 54.0f);
            vpn = glm::vec3(0.0f, 0.0f, 1.0f);
            vup = glm::vec3(0.0f, 1.0f, 0.0f);
            prp = glm::vec3(20.0f, 25.0f, 20.0f);
            
            min = glm::vec2(-20.0f, -5.0f);
            max = glm::vec2( 20.0f, 35.0f);
            
            front = 1.0f;
            back  = -35.0f;
            break;
    
        case 3:
            vrp = glm::vec3(16.0f, 0.0f, 54.0f);
            vpn = glm::vec3(1.0f, 0.0f, 1.0f);
            vup = glm::vec3(0.0f, 1.0f, 0.0f);
            prp = glm::vec3(0.0f, 25.0f, 20.0f * sqrt(2.0f));
            
            min = glm::vec2(-20.0f,-5.0f);
            max = glm::vec2( 20.0f, 35.0f);
            
            front = 1.0f;
            back  = -35.0f;
            break;
    
        case 4:
            vrp = glm::vec3(16.0f, 0.0f, 54.0f);
            vpn = glm::vec3(1.0f, 0.0f, 1.0f);
            vup = glm::vec3(-sin(10.0f * M_PI / 180.0f),
                             cos(10.0f * M_PI / 180.0f),
                             sin(10.0f * M_PI / 180.0f));
            prp = glm::vec3(0.0f, 25.0f, 20.0f * sqrt(2.0f));
            
            min = glm::vec2(-20.0f,-5.0f);
            max = glm::vec2( 20.0f, 35.0f);
            
            front = 1.0f;
            back  = -35.0f;
            break;
    }
    
    return current;
}

