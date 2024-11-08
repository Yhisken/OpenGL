#include "application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
//单例
Application* Application::mInstance = nullptr;

Application* Application::getInstance() {
	if (mInstance == nullptr) {
		mInstance = new Application();
	}
	return mInstance;
}


Application::Application() {

}

Application::~Application() {

}

bool Application::init(const int& width , const int& height )
{
	mWidth = width;
	mHeight = height;
	glfwInit();//初始化

	//设置主次版本号4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	//启用CORE模式（CORE和非立即渲染模式）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗体对象
	mWindow = glfwCreateWindow(mWidth, mHeight, "LearnOpenGL", NULL, NULL);

	if (mWindow == NULL) {
		return false;
	}

	//设置当前窗体为opengl绘制窗体
	glfwMakeContextCurrent(mWindow);

	//使用GLAD加载当前版本所有opengl函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallBack);

	//this就是当前全局的唯一的Application对象
	glfwSetWindowUserPointer(mWindow, this);
	glfwSetKeyCallback(mWindow, keyCallBack);

	//鼠标点击事件响应
	glfwSetMouseButtonCallback(mWindow, mouseCallBack);
	//鼠标移动事件响应
	glfwSetCursorPosCallback(mWindow, cursorCallBack);
	return true;
}

bool Application::update()
{
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}
	 
	glfwPollEvents(); //接收并分发窗口消息

	//GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//执行画布清理操作
	//GL_CALL用来错误检查的宏定义
	//checkError();//错误检查

	glfwSwapBuffers(mWindow);//切换双缓存

	return true;
}

void Application::destory()
{
	glfwTerminate();
}

void Application::frameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mResizeCallback != nullptr) {
		self->mResizeCallback(width, height);
	}

	//if (Application::getInstance()->mResizeCallback != nullptr) {
	//	Application::getInstance()->mResizeCallback(width, height);
	//}

}

void Application::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mKeyBoardCallback != nullptr) {
		self->mKeyBoardCallback(key, action, mods);
	}
}

void Application::mouseCallBack(GLFWwindow* window, int button, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mMouseCallback != nullptr) {
		self->mMouseCallback(button, action, mods);
	}
}

void Application::cursorCallBack(GLFWwindow* window, double xpos, double ypos)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mCursorCallback != nullptr) {
		self->mCursorCallback(xpos, ypos);
	}
}

void Application::getCursorPosition(double* xpos, double* ypos)
{
	glfwGetCursorPos(mWindow, xpos, ypos);
}

