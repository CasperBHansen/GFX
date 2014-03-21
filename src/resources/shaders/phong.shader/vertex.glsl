#version 110

attribute vec3 vtx;
attribute vec3 normal;
attribute vec3 tex;

uniform mat4 mv;
uniform mat4 mvp;

varying vec3 N;
varying vec3 P;

void main() {
    
    P = vtx;
    N = normal;
    
    gl_Position = mvp * vec4(vtx, 1.0);
}
