#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "wrapper/checkError.h"
#include "application/Application.h"

GLuint vao, program ,ebo;


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
		0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,
		0.5f,0.5f,0.0f,0.0f,0.0f,1.0f
	};
	unsigned int indices[] = {
		0,1,2,
		0,2,3
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

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	//�����������Լ������֣����ͣ��Ƿ��һ����ÿ�������С����������һ�������ƫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);//�󶨵�����
	//�����������Լ������֣����ͣ��Ƿ��һ����ÿ�������С����������һ�������ƫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);//��ebo���vao

	glBindVertexArray(0); //���VAO
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

void prepareShader() {
	//ShaderԴ����
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
	//����Shader����
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//Ϊshader��������shader����
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

	//����
	int success = 0;
	char infoLog[1024];
	//����
	glCompileShader(vertex);
	//���������
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		std::cout << "Error: SHADER COMPILE ERROR -- VERTEX" << "\n" << infoLog << std::endl;
	}
	//����
	glCompileShader(fragment);
	//���������
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
		std::cout << "Error: SHADER COMPILE ERROR -- FRAGMENT" << "\n" << infoLog << std::endl;
	}


	//����Program
	//GLuint program = 0;
	program = glCreateProgram();

	//vs fs����Program
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	//����
	glLinkProgram(program);
	//������Ӵ���
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		std::cout << "Error: SHADER LINK ERROR " << "\n" << infoLog << std::endl;
	}

	//����
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//ִ�л����������, GL_CALL����������ĺ궨��
	//��shader program
	glUseProgram(program);
	glBindVertexArray(vao); 
	//glDrawArrays(GL_TRIANGLES,0,3);//GL_TRIANGLES_STRIP/ FAN

	//modes , �����㣬���ͣ�0/ƫ��/��������
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); //���VAO
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

	//��Ⱦѭ��
	while (app->update()) {
		
		
		render();
	}

	app->destory();
	return 0;
}