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

#include <string>
using std::string;

#include <fstream>

Shader::Shader(const char * filename)
{
    valid = 0;
    program = glCreateProgram();
    this->filename = filename;
    
    // fall back on default shader, if no source is provided.
    if ( !(this->filename) ) {
        cerr << "No shader file provided, falling back on default shader." << endl;
        this->filename = "resources/shaders/default.shader";
    }
    
    // compile shaders
    compileShader(VERTEX_SHADER);
    compileShader(FRAGMENT_SHADER);
    compileShader(GEOMETRY_SHADER);
    
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

void Shader::compileShader(ShaderType type)
{
    const char * file, * src;
    
    switch (type) {
        
        case VERTEX_SHADER:
            file = "/vertex.glsl";
            break;
        
        case FRAGMENT_SHADER:
            file = "/fragment.glsl";
            break;
        
        case GEOMETRY_SHADER:
            file = "/geometry.glsl";
            break;
    }
    
    string path, line, source;
    path.append(filename);
    path.append(file);
    
    std::ifstream in(path.c_str());
    while ( std::getline(in, line) ) {
        source += line + "\n";
    }
    
    src = source.c_str();
    
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

GLenum Shader::getGLShaderType(ShaderType type)
{
    GLenum ret;
    switch (type) {
        
        case VERTEX_SHADER:
            ret = GL_VERTEX_SHADER;
            break;
        
        case FRAGMENT_SHADER:
            ret = GL_FRAGMENT_SHADER;
            break;
        
        case GEOMETRY_SHADER:
            ret = GL_GEOMETRY_SHADER;
            break;
    }
    
    return ret;
}

void Shader::use()
{
    if (isValid()) glUseProgram(program);
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
