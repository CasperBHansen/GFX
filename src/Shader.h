/*
 * Introduction to Computer Graphics
 *
 * Shader.h
 *
 */

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#define NUM_SHADERS 3

typedef enum {
    VERTEX_SHADER_PROGRAM,
    FRAGMENT_SHADER_PROGRAM,
    GEOMETRY_SHADER_PROGRAM
} ShaderType;

class Shader
{
public:
	Shader(const GLchar * vertexShaderSource   = NULL,
           const GLchar * fragmentShaderSource = NULL,
           const GLchar * geometryShaderSource = NULL);
	~Shader();
    
    GLuint getAttribLocation(const char * attrib)       { return glGetAttribLocation(program, attrib); }
    GLuint getUniformLocation(const char * uniform)     { return glGetUniformLocation(program, uniform); }
    
    void use();
    
    bool isValid();

protected:
    GLenum getGLShaderType(ShaderType type);
    void compileShader(ShaderType type, const GLchar * src);

private:
    GLuint program;
    GLuint shaders[3];
    
    GLint valid;
};

#endif // SHADER_H

