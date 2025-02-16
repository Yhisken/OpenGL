#pragma once
#include "cameraControl.h"

class TrackBallCameraControl : public CameraControl {
public:
	TrackBallCameraControl();
	~TrackBallCameraControl();

	void onCursor(double xpos, double ypos) override;
	void onScroll(float offset) override;
private:
	float mMoveSpeed = 0.01f;
	void pitch(float angle);
	void yaw(float angle);
};