#include "cameraControl.h"
#pragma once
#include "cameraControl.h"
#pragma warning(disable:4244)
CameraControl::CameraControl()
{

}

CameraControl::~CameraControl()
{
}

void CameraControl::onMouse(int button, int action, double xpos, double ypos)
{
	//std::cout << "OnMouse" << std::endl;
	bool pressed = action == GLFW_PRESS ? true : false;
	if (pressed) {
		mCurrentX = xpos;
		mCurrentY = ypos;
	}
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		mLeftMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mRightMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mMiddleMouseDown = pressed;
		break;
	}
}

void CameraControl::onCursor(double xpos, double ypos)
{
	//std::cout << "OnCursor" << std::endl;
}

void CameraControl::onKey(int key, int action, int mods)
{
	//std::cout << "OnKey" << std::endl;
	//���˵�repeat�����
	if (action == GLFW_REPEAT) {
		return;
	}
	//��ⰴ�»���̧�𣬸���һ������
	bool pressed = action == GLFW_PRESS ? true : false;
	//��¼��keyMap
	mKeyMap[key] = pressed;
}

void CameraControl::onScroll(float offset)
{
}


void CameraControl::update()
{
}
