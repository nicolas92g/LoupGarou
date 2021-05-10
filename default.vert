#version 330 core
layout(location = 0) in vec2 pos;

out vec2 uv;
out vec3 col;

uniform mat4 projection;
uniform mat4 taille;
uniform mat4 position;

void main(){
	gl_Position = taille * position  *   vec4(pos, 0, 1);
	uv = pos;
}
