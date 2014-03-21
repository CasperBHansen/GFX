/*
 * Introduction to Computer Graphics
 *
 * Shader.h
 *
 */

#ifndef SHADER_H
#define SHADER_H

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <glm/glm.hpp>

#define NUM_SHADERS 3

typedef enum {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
    GEOMETRY_SHADER
} ShaderType;

typedef struct {
    GLclampf Ka, Kd, Ks;
    
    struct Color3f {
        float r, b, g;
    };
} Material;

class Shader
{
public:
    Shader(const char * filename = NULL);
	~Shader();
    
    GLuint getAttribLocation(const char * attrib)
    { return glGetAttribLocation(program, attrib); }
    
    GLuint getUniformLocation(const char * uniform)
    { return glGetUniformLocation(program, uniform); }
    
    void uniform(const char * location, GLfloat v0);
    void uniform(const char * location, GLfloat v0, GLfloat v1);
    void uniform(const char * location, GLfloat v0, GLfloat v1, GLfloat v2);
    void uniform(const char * location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    
    void uniform(const char * location, const glm::vec3 vector);
    void uniform(const char * location, const glm::mat4 matrix);
    
    void use();
    
    bool isValid();

protected:
    void compileShader(ShaderType type);
    
    GLenum getGLShaderType(ShaderType type);

private:
    const char * filename;
    
    GLuint program;
    GLuint shaders[3];
    
    Material material;
    
    GLint valid;
};

#endif // SHADER_H

