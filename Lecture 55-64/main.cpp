#include <iostream>
#include"glframework/core.h"
#include"glframework/shader.h"
#include <assert.h>
#include "wrapper/checkError.h"
#include "application/Application.h"
#include "glframework/texture.h"
GLuint vao, program ,ebo; 
Shader* shader = nullptr;
Texture* texture = nullptr;
Texture* texture2 = nullptr;

void OnResize(int width, int height) {
	std::cout << "窗体最新大小" << width << "，" << height << std::endl;
	GL_CALL(glViewport(0, 0, width, height));
}
void OnKey(int key, int action, int mods) {
	std::cout << key << std::endl;
}

void prepareInterleavedBuffer() {
	//float vertices[] = {
	//	-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,
	//	0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
	//	0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,0.5f,1.0f
	//};
	float vertices[] = {
	-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,
	0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,10.0f,0.0f,
	0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,5,10
	};
	unsigned int indices[] = {
		0,1,2,
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

	//动态获取位置
	GLuint posLocation = glGetAttribLocation(shader->mProgram, "aPos");
	GLuint colorLocation = glGetAttribLocation(shader->mProgram, "aColor");
	GLuint uvLocation = glGetAttribLocation(shader->mProgram, "aUV");
	//动态获取Uniform编号
	// GLuint location = glGetUniformLocation(program,"time"); 
	// 设置变量的值
	// glUniform1f(location,0.5f);


	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(posLocation);
	//索引，该属性几个数字，类型，是否归一化，每个顶点大小，该属性在一个顶点的偏移量
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(colorLocation);//绑定的索引
	//索引，该属性几个数字，类型，是否归一化，每个顶点大小，该属性在一个顶点的偏移量
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(uvLocation);//绑定的索引
	//索引，该属性几个数字，类型，是否归一化，每个顶点大小，该属性在一个顶点的偏移量
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);//把ebo绑给vao

	glBindVertexArray(0); //解绑VAO
}

void prepareShader() {
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareTexture() {
	texture = new Texture("assets/textures/std-image.jpg", 0);
	texture2 = new Texture("assets/textures/wf.jpg", 1);
}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//执行画布清理操作, GL_CALL用来错误检查的宏定义

	//绑定shader program
	//glUseProgram(program);
	shader->begin();

	//glGetUniformLocation必须在UseProgram后面使用，也就是shader->begin后使用
	float color[] = { 0.5,0.3,0.4 };
	shader->setVector3("uColor", color);
	shader->setFloat("time", glfwGetTime());//传的变量在VS FS中声明后都可以使用，因为vs fs已经合成为了program
	shader->setInt("sampler", 0);
	shader->setInt("sampler", 1);

	glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES,0,3);//GL_TRIANGLES_STRIP/ FAN

	//modes , 几个点，类型，0/偏移/索引数组
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); //解绑VAO

	//解除绑定Shader，下一个三角形要换绑
	shader->end();
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
	prepareTexture(); 
	//渲染循环
	while (app->update()) {
	
		
		render();
	}

	app->destory();
	delete texture;
	return 0;
}