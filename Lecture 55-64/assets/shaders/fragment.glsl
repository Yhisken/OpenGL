#version 330 core
uniform sampler2D sampler;
uniform sampler2D sampler2;

out vec4 FragColor;
in vec3 color;
in vec3 pos;
in vec2 uv;
uniform vec3 uColor;
//uniform float time;
void main()
{
	vec4 color1 = texture(sampler, uv);
	vec4 color2 = texture(sampler2, uv);
	vec4 FinalColor = mix(color1, color2, 0.5);
	//FragColor = vec4(color, 1.0);
	FragColor = FinalColor;
}