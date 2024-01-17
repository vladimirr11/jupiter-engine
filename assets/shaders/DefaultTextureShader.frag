#version 410 core

uniform sampler2D uTextureSampler;
uniform vec4 uColor;
uniform int uTexScaler;

in vec2 vTexCoord; 
out vec4 fragColor;

void main() {
    fragColor = texture(uTextureSampler, vTexCoord * uTexScaler) * uColor;
}
