#pragma once

#ifndef APPLITCATION

#define APPLITCATION

#include <iostream>

#define app Application::getInstance() //宏 实例化

class GLFWwindow;

using ResizeCallback = void(*)(int width, int height);
using KeyBoardCallback = void(*)(int key, int action, int mods);
using MouseCallback = void(*)(int button , int action, int mods);
using CursorCallback = void(*)(double xpos, double ypos);
using ScrollCallback = void(*)( double yoffset);

class Application {
public:
	~Application();
	static Application* getInstance();

	bool init(const int& width = 800, const int& height = 600);

	bool update();

	void destory();
	
	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }
	void getCursorPosition(double* xpos, double* ypos);

	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyBoardCallback(KeyBoardCallback callback) { mKeyBoardCallback = callback; }
	void setMouseCallback(MouseCallback callback) { mMouseCallback = callback; }
	void setCursorCallback(CursorCallback callback) { mCursorCallback = callback; }
	void setScrollCallback(ScrollCallback callback) { mScrollCallback = callback; }
private:
	static void frameBufferSizeCallBack(GLFWwindow* window, int width, int height);
	static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallBack(GLFWwindow* window, int button, int action, int mods);
	static void cursorCallBack(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
private:
	static Application* mInstance;
	//窗口设置
	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };
	ResizeCallback mResizeCallback{ nullptr };
	KeyBoardCallback mKeyBoardCallback{ nullptr };
	MouseCallback mMouseCallback{ nullptr };
	CursorCallback mCursorCallback{ nullptr };
	ScrollCallback mScrollCallback{ nullptr };
	Application();
};

#endif