//on utilise la version 3.3 core
#version 330 core

//on recupere les vertices du vertex buffer
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUv;

//variables envoyées au fragment shader
out vec2 uv;
out vec3 normal;
out vec3 pixelPos;

//on recupere nos matrices sous la forme d' uniform buffers
uniform mat4 projection;
uniform mat4 vue; 
uniform mat4 model;

//fonction principale
void main(){
	//on donne les coordonnées du point modifié par toutes les matrices au vertex shader
	gl_Position =  projection * vue * model * vec4(pos , 1);

	//on donne les coordonnés uv au fragment shader
	uv = inUv;

	//indique la position de chaque pixel dans le fragment shader
	pixelPos = vec3(model * vec4(pos, 1.0));

	normal = inNormal;
}
