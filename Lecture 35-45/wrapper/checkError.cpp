#include "checkError.h"
#include <iostream>
#include <glad/glad.h>
#include <assert.h>
#include <string>

void checkError() {
	GLenum errorCode = (GLenum)glGetError();
	std::string error = " ";
	if (errorCode != GL_NO_ERROR) {
		switch (errorCode) {
		case GL_INVALID_ENUM: error = "GL_INVALID_ENUM"; break;
		case GL_INVALID_VALUE: error = "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION: error = "GL_INVALID_OPERATION"; break;
		case GL_OUT_OF_MEMORY: error = "GL_OUT_OF_MEMORY"; break;
		default:
			error = "UNKNOW";
			break;
		}
		std::cout << error << std::endl;
		//assert(false);//C++断言，根据传入的bool值决定程序是否停止
	}
}
