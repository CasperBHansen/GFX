/*
 * Introduction to Computer Graphics
 *
 * Object.cpp
 *
 */

#include "Object.h"

#include <iostream>
using std::cout;
using std::endl;

Object::Object(const glm::vec3 &position,
               const glm::vec3 &rotation,
               const glm::vec3 &scale)
{
    _position = position;
    _rotation = rotation;
	_scale    = scale;
}

Object::~Object()
{
	// destructor
}

glm::mat4 Object::getTransform()
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

void Object::setPosition(const glm::vec3 &vec)  { _position = vec; }
void Object::setRotation(const glm::vec3 &vec)  { _rotation = vec; }
void Object::setScale(const glm::vec3 &vec)     { _scale = vec; }

glm::vec3 Object::getPosition() const           { return _position; }
glm::vec3 Object::getRotation() const           { return _rotation; }
glm::vec3 Object::getScale() const              { return _scale; }

void Object::translate(const glm::vec3 &vec)    { _position += vec; }
void Object::rotate(const glm::vec3 &vec)       { _rotation += vec; }
void Object::scale(const glm::vec3 &vec)        { _scale *= vec; }

float Object::distanceTo(Object * object)
{
    return glm::distance(object->_position, _position);
}

