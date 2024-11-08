#pragma once
#include "perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
{
	mFovy = fov;
	mAspect = aspect;
	mNear = near;
	mFar = far;
}

PerspectiveCamera::~PerspectiveCamera()
{
}

glm::mat4 PerspectiveCamera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(mFovy), mAspect, mNear, mFar);
}
