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

const GLchar * defaultVertexShader   = NULL;
const GLchar * defaultFragmentShader = NULL;
const GLchar * defaultGeometryShader = NULL;

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
    if (valid) glUseProgram(program);
}

bool Shader::isValid()
{
    return valid;
}

