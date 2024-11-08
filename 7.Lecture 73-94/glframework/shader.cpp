#include "shader.h"
#include "shader.h"
#include "shader.h"
#include "shader.h"
#include <fstream>
#include"../wrapper/checkError.h"
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//声明装入Shader代码字符串的两个string
	std::string vertexCode;
	std::string fragmentCode;
	//声明用于读取vs跟fs文件的inFileStream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//保证ifstream遇到问题的时候可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream:: badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		//将文件输入流当中的字符串输入到stringStream里面
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//关闭文件
		vShaderFile.close();
		fShaderFile.close();

		//将字符串从stringStream当中读取出来，转化到code String当中
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR : Shader FIle Error" << e.what() << std::endl;
	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	//创建Shader程序
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//为shader程序输入shader代码
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);


	//编译
	glCompileShader(vertex);
	//检查编译错误
	checkShaderErrors(vertex, "COMPILE");
	//编译
	glCompileShader(fragment);
	//检查编译错误
	checkShaderErrors(fragment, "COMPILE");


	//创建Program
	//GLuint program = 0;
	mProgram = glCreateProgram();

	//vs fs放入Program
	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);

	//链接
	glLinkProgram(mProgram);
	//检查链接错误
	checkShaderErrors(mProgram, "LINK");


	//清理
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
	//通过名称拿到uniform的location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//通过Location更新Uniform变量的值
	glUniform1f(location, value);
}

void Shader::setVector3(const std::string& name, float x, float y, float z)
{
	//通过名称拿到uniform的location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//通过Location更新Uniform变量的值
	glUniform3f(location, x,y,z);
}

void Shader::setVector3(const std::string& name, const float* values)//传vec3的数组
{
	//通过名称拿到uniform的location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//通过Location更新Uniform变量的值，第二个参数：当前要更新的uniform变量，如果是数组，数组里面有多少个vec3
	glUniform3fv(location, 1, values);
}

void Shader::setInt(const std::string& name, int value)
{
	//通过名称拿到uniform的location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//通过Location更新Uniform变量的值，第二个参数：当前要更新的uniform变量，如果是数组，数组里面有多少个vec3
	glUniform1i(location, value);
}

void Shader::setMatrix4x4(const std::string& name, glm::mat4 value)
{
	//通过名称拿到uniform的location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//通过Location更新Uniform变量的值，第二个参数：当前要更新的uniform变量，如果是数组，数组里面有多少个vec3
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));//位置，传几个，是否转置，指向矩阵的指针
}
