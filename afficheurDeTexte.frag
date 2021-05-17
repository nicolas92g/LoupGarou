#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;

void main()
{    
    color = vec4(0.0, 0.0, 0.0, texture(text, TexCoords).r);
}  