#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "wrapper/checkError.h"

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height) {
	std::cout << "窗体最新大小" << width << "，" << height << std::endl;
	glViewport(0, 0, width, height);
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//窗口，key字母，scanmode物理按键码，action按下/抬起，mods是否有shift/ctrl
	std::cout << "按下了：" << key << std::endl;
	std::cout << "行为：" << action << std::endl;
	std::cout << "mods：" << mods << std::endl;
}


int main() {
	glfwInit();//初始化

	//设置主次版本号4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	//启用CORE模式（CORE和非立即渲染模式）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗体对象
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	//设置当前窗体为opengl绘制窗体
	glfwMakeContextCurrent(window);

	//设置监听，监听窗体大小变化的消息
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);

	//设置监听键盘事件
	glfwSetKeyCallback(window, keyCallBack);

	//使用GLAD加载当前版本所有opengl函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//设置视口大小和清理颜色
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//渲染循环
	while (!glfwWindowShouldClose(window)) {
		
		glfwPollEvents(); //接收并分发窗口消息

		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//执行画布清理操作
		//GL_CALL用来错误检查的宏定义
		//checkError();//错误检查

		glfwSwapBuffers(window);//切换双缓存
	}

	glfwTerminate();
	return 0;
}