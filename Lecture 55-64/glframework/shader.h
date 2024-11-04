#pragma once
#ifndef SHADER
#define SHADER
#include"core.h"
class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();//��ʼʹ�õ�ǰ��Shader�������л��󶨵�Shader��״̬����
	void end();//����ʹ�õ�ǰ��Shader�������л��󶨵�Shader��״̬����
	void setFloat(const std::string& name, float value);
	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, const float* values);
	void setInt(const std::string& name, int value);
public:
	GLuint mProgram{ 0 };

private:
	//shader program, type: COMPILE / LINK
	void checkShaderErrors(GLuint target, std::string type);
};
#endif