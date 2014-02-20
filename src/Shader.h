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

static const GLchar * defaultVertexShader = "       \n\
#version 110                                        \n\
                                                    \n\
attribute vec3 vtx;                                 \n\
                                                    \n\
uniform mat4 mvp;                                   \n\
                                                    \n\
void main() {                                       \n\
    gl_Position = mvp * vec4(vtx, 1.0);             \n\
}";

static const GLchar * defaultFragmentShader = "     \n\
#version 110                                        \n\
                                                    \n\
uniform vec3 color;                                 \n\
                                                    \n\
void main() {                                       \n\
    gl_FragColor = vec4(color, 1.0);                \n\
}";

static const GLchar * defaultGeometryShader = "     \n\
#version 110                                        \n\
                                                    \n\
void main() {                                       \n\
}";

class Shader
{
public:
	Shader(const GLchar * vertexShaderSource   = defaultVertexShader,
           const GLchar * fragmentShaderSource = defaultFragmentShader,
           const GLchar * geometryShaderSource = defaultGeometryShader);
	~Shader();
    
    GLuint getAttribLocation(const char * attrib)       { return glGetAttribLocation(program, attrib); }
    GLuint getUniformLocation(const char * uniform)     { return glGetUniformLocation(program, uniform); }
    
    void uniform(const char * location, GLfloat v0);
    void uniform(const char * location, GLfloat v0, GLfloat v1);
    void uniform(const char * location, GLfloat v0, GLfloat v1, GLfloat v2);
    void uniform(const char * location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    
    void uniformMatrix4fv(const char * location, const GLfloat * value);
    
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

