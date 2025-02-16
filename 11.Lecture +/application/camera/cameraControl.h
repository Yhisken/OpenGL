#ifndef CAMERA_CONTROL
#define CAMERA_CONTROL

#pragma once
#include "camera.h"
#include<map>
#pragma warning(disable:4244)


class CameraControl {

public:
	CameraControl();
	~CameraControl();

	virtual void onMouse(int button, int action, double xpos, double ypos);
	virtual void onCursor(double xpos, double ypos);
	virtual void onKey(int key, int action, int mods);
	virtual void onScroll(float offset); //+1， -1
	virtual void update();

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float s) { mSensitivity = s; }
	void setScaleSpeed(float s) { mScaleSpeed = s; }
	//鼠标按键状态
	bool mLeftMouseDown = false;
	bool mRightMouseDown = false;
	bool mMiddleMouseDown = false;

	//当前鼠标的位置
	float mCurrentX = 0.0f, mCurrentY = 0.0f;

	//敏感度
	float mSensitivity = 0.2f;

	//记录键盘相关按键的按下状态
	std::map<int, bool> mKeyMap;

	//存储当前k控制的那一个相机
	Camera* mCamera = nullptr;

	//记录相机缩放的速度
	float mScaleSpeed = 0.2f;
};




#endif