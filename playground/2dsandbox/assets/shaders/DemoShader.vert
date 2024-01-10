#version 450 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

uniform mat4 projViewMatrix;
uniform mat4 modelTransform;

out vec2 vTexCoord;
void main() {
    gl_Position = projViewMatrix * modelTransform * vec4(pos.x, pos.y, pos.z, 1.0);
    vTexCoord = texCoord;
}
