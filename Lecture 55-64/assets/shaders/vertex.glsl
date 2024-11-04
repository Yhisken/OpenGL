#version 460 core
//layout (location = 0 ) in vec3 aPos;
//layout (location = 1 ) in vec3 aColor;
in vec3 aPos;
in vec3 aColor;
in vec2 aUV;
out vec3 color;
out vec3 pos;
out vec2 uv;
uniform float time;
void main()
{
	float dx = 0.3;
	float offsetX = sin(time) * dx;
	gl_Position = vec4(aPos.x+offsetX,aPos.y,aPos.z,1.0);
	color = aColor*((sin(time)+1)/2);
	pos = vec3(aPos.x,aPos.y,aPos.z);
	uv = aUV;
}