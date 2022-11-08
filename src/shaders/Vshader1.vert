#version 460 core

// variables stored in format [space]_name

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;


void main() {
    UV = vertexUV;
    gl_Position = vec4(vert.x / 720.0 - 1.0, vert.y / 405.0 - 1.0, 0.0, 1.0);
}
