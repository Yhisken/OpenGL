#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "wrapper/checkError.h"

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height) {
	std::cout << "�������´�С" << width << "��" << height << std::endl;
	glViewport(0, 0, width, height);
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//���ڣ�key��ĸ��scanmode�������룬action����/̧��mods�Ƿ���shift/ctrl
	std::cout << "�����ˣ�" << key << std::endl;
	std::cout << "��Ϊ��" << action << std::endl;
	std::cout << "mods��" << mods << std::endl;
}


int main() {
	glfwInit();//��ʼ��

	//�������ΰ汾��4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	//����COREģʽ��CORE�ͷ�������Ⱦģʽ��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�����������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	//���õ�ǰ����Ϊopengl���ƴ���
	glfwMakeContextCurrent(window);

	//���ü��������������С�仯����Ϣ
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);

	//���ü��������¼�
	glfwSetKeyCallback(window, keyCallBack);

	//ʹ��GLAD���ص�ǰ�汾����opengl����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//�����ӿڴ�С��������ɫ
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		
		glfwPollEvents(); //���ղ��ַ�������Ϣ

		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//ִ�л����������
		//GL_CALL����������ĺ궨��
		//checkError();//������

		glfwSwapBuffers(window);//�л�˫����
	}

	glfwTerminate();
	return 0;
}