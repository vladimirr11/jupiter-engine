#version 450 core

uniform sampler2D uTextureSampler;
in vec2 vTexCoord; 

out vec4 fragColor;

void main() {
    fragColor = texture(uTextureSampler, vTexCoord);
}
