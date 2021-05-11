#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D tex;
uniform float time;

void main(){
	const float f = 0.3f;
	color = texture(tex, uv);
}
