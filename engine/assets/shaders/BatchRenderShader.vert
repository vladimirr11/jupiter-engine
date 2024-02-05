#version 410 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTexScaler;
layout (location = 4) in float aTexSlot;

uniform mat4 projViewMatrix;

out vec4 color;    
out vec2 texCoord;    
out float texScaler;    
out float texSlot;  

void main() {
    gl_Position = projViewMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = aColor;
    texCoord = aTexCoord;
    texScaler = aTexScaler;
    texSlot = aTexSlot;
}
