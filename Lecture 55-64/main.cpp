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
	std::cout << "�������´�С" << width << "��" << height << std::endl;
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

	glBindBuffer(GL_ARRAY_BUFFER, vbo); //��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//������

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//��̬��ȡλ��
	GLuint posLocation = glGetAttribLocation(shader->mProgram, "aPos");
	GLuint colorLocation = glGetAttribLocation(shader->mProgram, "aColor");
	GLuint uvLocation = glGetAttribLocation(shader->mProgram, "aUV");
	//��̬��ȡUniform���
	// GLuint location = glGetUniformLocation(program,"time"); 
	// ���ñ�����ֵ
	// glUniform1f(location,0.5f);


	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(posLocation);
	//�����������Լ������֣����ͣ��Ƿ��һ����ÿ�������С����������һ�������ƫ����
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(colorLocation);//�󶨵�����
	//�����������Լ������֣����ͣ��Ƿ��һ����ÿ�������С����������һ�������ƫ����
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(uvLocation);//�󶨵�����
	//�����������Լ������֣����ͣ��Ƿ��һ����ÿ�������С����������һ�������ƫ����
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);//��ebo���vao

	glBindVertexArray(0); //���VAO
}

void prepareShader() {
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareTexture() {
	texture = new Texture("assets/textures/std-image.jpg", 0);
	texture2 = new Texture("assets/textures/wf.jpg", 1);
}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//ִ�л����������, GL_CALL����������ĺ궨��

	//��shader program
	//glUseProgram(program);
	shader->begin();

	//glGetUniformLocation������UseProgram����ʹ�ã�Ҳ����shader->begin��ʹ��
	float color[] = { 0.5,0.3,0.4 };
	shader->setVector3("uColor", color);
	shader->setFloat("time", glfwGetTime());//���ı�����VS FS�������󶼿���ʹ�ã���Ϊvs fs�Ѿ��ϳ�Ϊ��program
	shader->setInt("sampler", 0);
	shader->setInt("sampler", 1);

	glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES,0,3);//GL_TRIANGLES_STRIP/ FAN

	//modes , �����㣬���ͣ�0/ƫ��/��������
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); //���VAO

	//�����Shader����һ��������Ҫ����
	shader->end();
}


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

	prepareShader();
	prepareInterleavedBuffer();
	prepareTexture(); 
	//��Ⱦѭ��
	while (app->update()) {
	
		
		render();
	}

	app->destory();
	delete texture;
	return 0;
}