#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "wrapper/checkError.h"
#include "application/Application.h"



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
		0.0f,0.5f,0.0f,0.0f,0.0f,1.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo); //绑定
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//传数据

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);//绑定的索引
	//索引，该属性几个数字，类型，是否归一化，每个顶点大小，该属性在一个顶点的偏移量
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));


	glBindVertexArray(0); //解绑VAO
}
void prepareSingleBuffer() {
	float positions[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f
	};
	float colors[]{
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f
	};
	GLuint posVbo, colorVbo;
	glGenBuffers(1, &posVbo);
	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}
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

	//渲染循环
	while (app->update()) {
		
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//执行画布清理操作, GL_CALL用来错误检查的宏定义

	}

	app->destory();
	return 0;
}