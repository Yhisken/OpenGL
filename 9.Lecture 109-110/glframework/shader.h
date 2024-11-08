#ifndef SHADER
#define SHADER
#pragma once
#include"core.h"
class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();//开始使用当前的Shader，用于切换绑定的Shader（状态机）
	void end();//结束使用当前的Shader，用于切换绑定的Shader（状态机）
	void setFloat(const std::string& name, float value);
	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, const float* values);
	void setInt(const std::string& name, int value);
	void setMatrix4x4(const std::string& name, glm::mat4 value);
public:
	GLuint mProgram{ 0 };

private:
	//shader program, type: COMPILE / LINK
	void checkShaderErrors(GLuint target, std::string type);
};
#endif