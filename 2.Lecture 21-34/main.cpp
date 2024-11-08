#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "wrapper/checkError.h"
#include "application/Application.h"



void OnResize(int width, int height) {
	std::cout << "�������´�С" << width << "��" << height << std::endl;
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

	glBindBuffer(GL_ARRAY_BUFFER, vbo); //��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//������

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);//�󶨵�����
	//�����������Լ������֣����ͣ��Ƿ��һ����ÿ�������С����������һ�������ƫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));


	glBindVertexArray(0); //���VAO
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
//	//����һ��VBO��û�з����Դ�
//	GLuint vbo = 0;
//	GL_CALL(glGenBuffers(1, &vbo));
//	//��
//	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//	//��������
//	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//	//����VBO
//	GL_CALL(glDeleteBuffers(1, &vbo));
//
//}
int main() {
	if (!app->init(800, 600)) {
		return -1;
	}
	////���ü��������������С�仯����Ϣ
	app->setResizeCallback(OnResize);

	////���ü��������¼�
	app->setKeyBoardCallback(OnKey);

	//�����ӿڴ�С��������ɫ
	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	//��Ⱦѭ��
	while (app->update()) {
		
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//ִ�л����������, GL_CALL����������ĺ궨��

	}

	app->destory();
	return 0;
}