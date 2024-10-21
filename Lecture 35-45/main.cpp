#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "wrapper/checkError.h"
#include "application/Application.h"

GLuint vao, program ,ebo;


void OnResize(int width, int height) {
	std::cout << "窗体最新大小" << width << "，" << height << std::endl;
	GL_CALL(glViewport(0, 0, width, height));
}
void OnKey(int key, int action, int mods) {
	std::cout << key << std::endl;
}

void prepareInterleavedBuffer() {
	float vertices[] = {
		-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,
		0.5f,0.5f,0.0f,0.0f,0.0f,1.0f
	};
	unsigned int indices[] = {
		0,1,2,
		0,2,3
	};
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo); //绑定
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//传数据

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	//索引，该属性几个数字，类型，是否归一化，每个顶点大小，该属性在一个顶点的偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);//绑定的索引
	//索引，该属性几个数字，类型，是否归一化，每个顶点大小，该属性在一个顶点的偏移量
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);//把ebo绑给vao

	glBindVertexArray(0); //解绑VAO
}
//void prepareSingleBuffer() {
//	float positions[] = {
//	-0.5f,-0.5f,0.0f,
//	0.5f,-0.5f,0.0f,
//	0.0f,0.5f,0.0f
//	};
//	float colors[]{
//		1.0f,0.0f,0.0f,
//		0.0f,1.0f,0.0f,
//		0.0f,0.0f,1.0f
//	};
//	GLuint posVbo, colorVbo;
//	glGenBuffers(1, &posVbo);
//	glGenBuffers(1, &colorVbo);
//	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
//
//	GLuint vao = 0;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//	glBindVertexArray(0);
//}
//void prepareVBO() {
//	float vertices[] = {
//		-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
//		0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
//		0.0f,0.5f,0.0f,0.0f,0.0f,1.0f
//	};
//	//创建一个VBO还没有分配显存
//	GLuint vbo = 0;
//	GL_CALL(glGenBuffers(1, &vbo));
//	//绑定
//	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//	//传输数据
//	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//	//销毁VBO
//	GL_CALL(glDeleteBuffers(1, &vbo));
//
//}

void prepareShader() {
	//Shader源代码
	const char* vertexShaderSource =
		"#version 460 core\n"
		"layout (location = 0 ) in vec3 aPos;\n"
		"layout (location = 1 ) in vec3 aColor;\n"
		"out vec3 color;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"color = aColor;\n"
		"}\0";
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 color;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(color, 1.0);\n"
		"}\n\0";
	//创建Shader程序
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//为shader程序输入shader代码
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

	//编译
	int success = 0;
	char infoLog[1024];
	//编译
	glCompileShader(vertex);
	//检查编译错误
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		std::cout << "Error: SHADER COMPILE ERROR -- VERTEX" << "\n" << infoLog << std::endl;
	}
	//编译
	glCompileShader(fragment);
	//检查编译错误
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
		std::cout << "Error: SHADER COMPILE ERROR -- FRAGMENT" << "\n" << infoLog << std::endl;
	}


	//创建Program
	//GLuint program = 0;
	program = glCreateProgram();

	//vs fs放入Program
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	//链接
	glLinkProgram(program);
	//检查链接错误
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		std::cout << "Error: SHADER LINK ERROR " << "\n" << infoLog << std::endl;
	}

	//清理
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//执行画布清理操作, GL_CALL用来错误检查的宏定义
	//绑定shader program
	glUseProgram(program);
	glBindVertexArray(vao); 
	//glDrawArrays(GL_TRIANGLES,0,3);//GL_TRIANGLES_STRIP/ FAN

	//modes , 几个点，类型，0/偏移/索引数组
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); //解绑VAO
}


int main() {
	if (!app->init(800, 600)) {
		return -1;
	}
	////设置监听，监听窗体大小变化的消息
	app->setResizeCallback(OnResize);

	////设置监听键盘事件
	app->setKeyBoardCallback(OnKey);

	//设置视口大小和清理颜色
	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	prepareShader();
	prepareInterleavedBuffer();

	//渲染循环
	while (app->update()) {
		
		
		render();
	}

	app->destory();
	return 0;
}