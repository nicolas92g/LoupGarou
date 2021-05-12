#version 330 core
//on recupere les coordonées uv venant du vertex shader
in vec2 uv;

//valeurs sortant du fragment shader
out vec4 color;


uniform sampler2D tex;//on recupere une texture
uniform float alpha;//filtre alpha
uniform vec3 filtre = vec3(1);//filtre de couleur

void main(){
	//on creer la couleur qui va sortir du fragment shader
	color = texture(tex, uv);
	color.a -= alpha;
	color.rgb *= filtre;
}
