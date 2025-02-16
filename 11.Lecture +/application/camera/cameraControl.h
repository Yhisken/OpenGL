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
	virtual void onScroll(float offset); //+1�� -1
	virtual void update();

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float s) { mSensitivity = s; }
	void setScaleSpeed(float s) { mScaleSpeed = s; }
	//��갴��״̬
	bool mLeftMouseDown = false;
	bool mRightMouseDown = false;
	bool mMiddleMouseDown = false;

	//��ǰ����λ��
	float mCurrentX = 0.0f, mCurrentY = 0.0f;

	//���ж�
	float mSensitivity = 0.2f;

	//��¼������ذ����İ���״̬
	std::map<int, bool> mKeyMap;

	//�洢��ǰk���Ƶ���һ�����
	Camera* mCamera = nullptr;

	//��¼������ŵ��ٶ�
	float mScaleSpeed = 0.2f;
};




#endif