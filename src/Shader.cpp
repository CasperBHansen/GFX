/*
 * Introduction to Computer Graphics
 *
 * Shader.cpp
 *
 */

#include "Shader.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cstring>

Shader::Shader(const GLchar * vertexShaderSource,
               const GLchar * fragmentShaderSource,
               const GLchar * geometryShaderSource)
{
    valid = 0;
    program = glCreateProgram();
    
    // compile shaders
    compileShader(VERTEX_SHADER_PROGRAM, vertexShaderSource);
    compileShader(FRAGMENT_SHADER_PROGRAM, fragmentShaderSource);
    compileShader(GEOMETRY_SHADER_PROGRAM, geometryShaderSource);
    
    // link shader program
    GLint status;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLchar info[1024];
        glGetProgramInfoLog(program, sizeof(info), NULL, info);
        cerr << "Error linking program: '" << info << '\'' << endl;
    }
    
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    valid = status;
}

Shader::~Shader()
{
    glUseProgram(0);
    
    for (int i = 0; i < NUM_SHADERS; ++i) {
        if (!shaders[i]) continue;
        
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    
    glDeleteProgram(program);
}

GLenum Shader::getGLShaderType(ShaderType type)
{
    GLenum ret;
    switch (type) {
        
        case VERTEX_SHADER_PROGRAM:
            ret = GL_VERTEX_SHADER;
            break;
        
        case FRAGMENT_SHADER_PROGRAM:
            ret = GL_FRAGMENT_SHADER;
            break;
        
        case GEOMETRY_SHADER_PROGRAM:
            ret = GL_GEOMETRY_SHADER;
            break;
    }
    
    return ret;
}

void Shader::compileShader(ShaderType type, const GLchar * src)
{
    GLenum glType = getGLShaderType(type); 
    shaders[type] = glCreateShader(glType);
    glShaderSource(shaders[type], 1, &src, NULL);
    glCompileShader(shaders[type]);
    
    GLint status;
    glGetShaderiv(shaders[type], GL_COMPILE_STATUS, &status);
    if (!status) {
        GLchar info[1024];
        glGetShaderInfoLog(shaders[type], sizeof(info), NULL, info);
        cerr << "Error compiling shader type " << glType << ": '" << info << '\'' << endl;
    }
    
    glAttachShader(program, shaders[type]);
}

void Shader::use()
{
    glUseProgram(program);
}

bool Shader::isValid()
{
    return valid;
}

void Shader::uniform(const char * location, GLfloat v0)
{
    glUniform1f(getUniformLocation(location), v0);
}

void Shader::uniform(const char * location, GLfloat v0, GLfloat v1)
{
    glUniform2f(getUniformLocation(location), v0, v1);
}

void Shader::uniform(const char * location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    glUniform3f(getUniformLocation(location), v0, v1, v2);
}

void Shader::uniform(const char * location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    glUniform4f(getUniformLocation(location), v0, v1, v2, v3);
}

void Shader::uniformMatrix4fv(const char * location, const GLfloat * value)
{
    glUniformMatrix4fv(getUniformLocation(location), 1, GL_FALSE, value);
}
