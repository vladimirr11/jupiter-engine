#version 410 core

uniform sampler2D uTextureSampler;
uniform vec4 uColor;
uniform int uTexScaler;
uniform int uTexFlag; // Indicate if to use texture or not

in vec2 vTexCoord; 
out vec4 fragColor;

void main() {
    fragColor = uTexFlag * texture(uTextureSampler, vTexCoord * uTexScaler) * uColor + (1 - uTexFlag) * uColor;
}
