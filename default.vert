#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 inUv;

out vec3 col;
out vec2 uv;

uniform mat4 projection;
uniform mat4 model;

void main(){
	gl_Position =  projection * model * vec4(pos , 1);
	uv = inUv;
}
