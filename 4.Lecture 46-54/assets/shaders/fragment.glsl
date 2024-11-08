#version 330 core
out vec4 FragColor;
in vec3 color;
in vec3 pos;
uniform vec3 uColor;
//uniform float time;
void main()
{
	FragColor = vec4(uColor, 1.0);
}