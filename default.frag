#version 330 core

in vec2 uv;
in vec3 col;

out vec4 color;

uniform sampler2D tex;

void main(){
	color.rgb = col;//texture(tex, uv);
	color.a = 1;
}
