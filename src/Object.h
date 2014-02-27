/*
 * Introduction to Computer Graphics
 *
 * Object.h
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Types.h"

class Object
{
public:
	Object(const glm::vec3 &position = glm::vec3(0,0,0),
           const glm::vec3 &rotation = glm::vec3(0,0,0),
           const glm::vec3 &scale    = glm::vec3(1,1,1));
	virtual ~Object();
    
    virtual glm::mat4 getTransform();
    
    void setPosition(const glm::vec3 &vec);
    void setRotation(const glm::vec3 &vec);
    void setScale(const glm::vec3 &vec);
    
    void translate(const glm::vec3 &vec);
    void rotate(const glm::vec3 &vec);
    void scale(const glm::vec3 &vec);
    
    float distanceTo(Object * object);
    
protected:
    glm::vec3 _position;
    
private:
    glm::mat4 matrix;
    
    glm::vec3 _scale;
    glm::vec3 _rotation;
};

#endif // OBJECT_H

