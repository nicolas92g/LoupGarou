#version 330 core
//on recupere les coordonées uv venant du vertex shader
in vec2 uv;
in vec3 normal;
in vec3 pixelPos;

//valeurs sortant du fragment shader
out vec4 color;

//variables locales
const vec3 positionLumiere = vec3(-1, 2, 0.5);
const vec3 couleurLumiere = vec3(1, 0.9, 0.8);

uniform sampler2D tex;//on recupere une texture

void main(){
	//lumiere ambiente
    vec3 ambient = 0.2 * couleurLumiere;

	//lumiere diffuse 
	vec3 N = normalize(normal);
	vec3 rayon = normalize(positionLumiere - pixelPos);

	vec3 diffuse = max(dot(N, rayon), 0.0) * couleurLumiere;

	//on creer la couleur qui va sortir du fragment shader
    color = vec4(ambient + diffuse, 1) * texture(tex, uv);
}
