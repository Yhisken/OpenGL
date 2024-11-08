#include "application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
//����
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
	glfwInit();//��ʼ��

	//�������ΰ汾��4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	//����COREģʽ��CORE�ͷ�������Ⱦģʽ��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�����������
	mWindow = glfwCreateWindow(mWidth, mHeight, "LearnOpenGL", NULL, NULL);

	if (mWindow == NULL) {
		return false;
	}

	//���õ�ǰ����Ϊopengl���ƴ���
	glfwMakeContextCurrent(mWindow);

	//ʹ��GLAD���ص�ǰ�汾����opengl����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallBack);

	//this���ǵ�ǰȫ�ֵ�Ψһ��Application����
	glfwSetWindowUserPointer(mWindow, this);
	glfwSetKeyCallback(mWindow, keyCallBack);

	//������¼���Ӧ
	glfwSetMouseButtonCallback(mWindow, mouseCallBack);
	//����ƶ��¼���Ӧ
	glfwSetCursorPosCallback(mWindow, cursorCallBack);
	return true;
}

bool Application::update()
{
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}
	 
	glfwPollEvents(); //���ղ��ַ�������Ϣ

	//GL_CALL(glClear(GL_COLOR_BUFFER_BIT));//ִ�л����������
	//GL_CALL����������ĺ궨��
	//checkError();//������

	glfwSwapBuffers(mWindow);//�л�˫����

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

