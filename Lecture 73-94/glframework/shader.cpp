#include "shader.h"
#include "shader.h"
#include "shader.h"
#include "shader.h"
#include <fstream>
#include"../wrapper/checkError.h"
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//����װ��Shader�����ַ���������string
	std::string vertexCode;
	std::string fragmentCode;
	//�������ڶ�ȡvs��fs�ļ���inFileStream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//��֤ifstream���������ʱ������׳��쳣
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream:: badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		//���ļ����������е��ַ������뵽stringStream����
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//�ر��ļ�
		vShaderFile.close();
		fShaderFile.close();

		//���ַ�����stringStream���ж�ȡ������ת����code String����
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR : Shader FIle Error" << e.what() << std::endl;
	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	//����Shader����
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//Ϊshader��������shader����
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);


	//����
	glCompileShader(vertex);
	//���������
	checkShaderErrors(vertex, "COMPILE");
	//����
	glCompileShader(fragment);
	//���������
	checkShaderErrors(fragment, "COMPILE");


	//����Program
	//GLuint program = 0;
	mProgram = glCreateProgram();

	//vs fs����Program
	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);

	//����
	glLinkProgram(mProgram);
	//������Ӵ���
	checkShaderErrors(mProgram, "LINK");


	//����
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}
Shader::~Shader() {

}
void Shader::begin() {
	GL_CALL(glUseProgram(mProgram));
}
void Shader::end() {
	GL_CALL(glUseProgram(0));
}
void Shader::checkShaderErrors(GLuint target, std::string type)
{
	int success = 0;
	char infoLog[1024];
	if (type == "COMPILE") {
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(target, 1024, NULL, infoLog);
			std::cout << "Error: SHADER COMPILE ERROR -- FRAGMENT" << "\n" << infoLog << std::endl;
		}
	}
	else if(type == "LINK")
	{
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(target, 1024, NULL, infoLog);
			std::cout << "Error: SHADER LINK ERROR " << "\n" << infoLog << std::endl;
		}
	}
	else {
		std::cout << "Error: Check shader errors Type is wrong" << std::endl;
	}
}
void Shader::setFloat(const std::string& name, float value)
{
	//ͨ�������õ�uniform��location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//ͨ��Location����Uniform������ֵ
	glUniform1f(location, value);
}

void Shader::setVector3(const std::string& name, float x, float y, float z)
{
	//ͨ�������õ�uniform��location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//ͨ��Location����Uniform������ֵ
	glUniform3f(location, x,y,z);
}

void Shader::setVector3(const std::string& name, const float* values)//��vec3������
{
	//ͨ�������õ�uniform��location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//ͨ��Location����Uniform������ֵ���ڶ�����������ǰҪ���µ�uniform��������������飬���������ж��ٸ�vec3
	glUniform3fv(location, 1, values);
}

void Shader::setInt(const std::string& name, int value)
{
	//ͨ�������õ�uniform��location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//ͨ��Location����Uniform������ֵ���ڶ�����������ǰҪ���µ�uniform��������������飬���������ж��ٸ�vec3
	glUniform1i(location, value);
}

void Shader::setMatrix4x4(const std::string& name, glm::mat4 value)
{
	//ͨ�������õ�uniform��location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//ͨ��Location����Uniform������ֵ���ڶ�����������ǰҪ���µ�uniform��������������飬���������ж��ٸ�vec3
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));//λ�ã����������Ƿ�ת�ã�ָ������ָ��
}
