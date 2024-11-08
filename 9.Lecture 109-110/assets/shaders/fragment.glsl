#version 330 core
uniform sampler2D sampler;
uniform sampler2D sampler2;

out vec4 FragColor;
//in vec3 color;
in vec3 pos;
in vec2 uv;
uniform vec3 uColor;
uniform float width;
uniform float height;
//uniform float time;
void main()
{
	////获取当前像素对应纹素的具体位置
	//vec2 location = uv * vec2(width, height);
	////计算当前像素对应纹素具体位置在xy方向上的变化量
	//vec2 dx = dFdx(location);
	//vec2 dy = dFdy(location);
	////选最大的Delta
	//float maxDelta = sqrt(max(dot(dx, dx), dot(dy, dy)));
	//float L = log2(maxDelta);
	////计算出level
	//int level = max(int(L + 0.5), 0);

	vec4 color1 = texture(sampler, uv);
	//vec4 color2 = texture(sampler2, uv);
	//vec4 FinalColor = mix(color1, color2, 0.5);
	FragColor = color1;
	//FragColor = FinalColor;
}