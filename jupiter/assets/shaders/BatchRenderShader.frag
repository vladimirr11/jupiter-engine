#version 410 core

out vec4 fragColor;

uniform sampler2D uSampler[32];

in vec4 color;    
in vec2 texCoord;    
in float texScaler;    
in float texSlot;  

void main() {
	fragColor = texture(uSampler[int(texSlot)], texCoord * texScaler) * color;
}
