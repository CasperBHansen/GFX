#version 110

attribute vec3 vtx;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(vtx, 1.0);
}
