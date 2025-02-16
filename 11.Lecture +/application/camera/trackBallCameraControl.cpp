#include "trackBallCameraControl.h"
#include "trackBallCameraControl.h"
#include "trackBallCameraControl.h"


TrackBallCameraControl::TrackBallCameraControl()
{

}

TrackBallCameraControl::~TrackBallCameraControl()
{

}

void TrackBallCameraControl::onCursor(double xpos, double ypos)
{
	if (mLeftMouseDown) {
		//��������
		float deltaX = (xpos - mCurrentX) * mSensitivity;
		float deltaY = (ypos - mCurrentY) * mSensitivity;
		//�ֿ�����Pitch��Yaw
		pitch(-deltaY);
		yaw(-deltaX);
	}
	else if (mMiddleMouseDown) {
		//��������
		float deltaX = (xpos - mCurrentX) * mMoveSpeed;
		float deltaY = (ypos - mCurrentY) * mMoveSpeed;
		mCamera->mPosition += mCamera->mUp * deltaY;
		mCamera->mPosition -= mCamera->mRight * deltaX;
	}
	mCurrentX = xpos;
	mCurrentY = ypos;
}


void TrackBallCameraControl::pitch(float angle)
{
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f); //1��ʾλ�ã�0��ʾ����
}

void TrackBallCameraControl::yaw(float angle)
{
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f); //1��ʾλ�ã�0��ʾ����
}

void TrackBallCameraControl::onScroll(float offset)
{
	mCamera->scale(mScaleSpeed*offset);
}