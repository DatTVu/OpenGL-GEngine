#include "stdafx.h"
#include "Camera.h"


Camera::Camera(Vector3 worldCamPos, Vector3 worldTargetPos)
{
	cameraPos = worldCamPos;
	targetPos = worldTargetPos;
	upVector = Vector3(0.0, 1.0, 0.0);
	aspectRatio = (float)(Globals::screenWidth / Globals::screenHeight);
}


Camera::~Camera()
{
}

Matrix Camera::CalculateViewMatrix() {
	Matrix inverseCamTranMat;
	/*inverseCamTranMat.m[3][0] = -cameraPos.x;
	inverseCamTranMat.m[3][1] = -cameraPos.y;
	inverseCamTranMat.m[3][2] = -cameraPos.z;*/
	inverseCamTranMat.SetTranslation(-cameraPos);

	Matrix inverseCamRotMat;
	
	Vector3 zaxis = (cameraPos-targetPos).Normalize();
	Vector3 xaxis = (upVector.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	inverseCamRotMat.m[0][0] = xaxis.x; inverseCamRotMat.m[0][1] = yaxis.x; inverseCamRotMat.m[0][2] = zaxis.x; inverseCamRotMat.m[0][3] = 0.0;
	inverseCamRotMat.m[1][0] = xaxis.y; inverseCamRotMat.m[1][1] = yaxis.y; inverseCamRotMat.m[1][2] = zaxis.y; inverseCamRotMat.m[1][3] = 0.0;
	inverseCamRotMat.m[2][0] = xaxis.z; inverseCamRotMat.m[2][1] = yaxis.z; inverseCamRotMat.m[2][2] = zaxis.z; inverseCamRotMat.m[2][3] = 0.0;
	inverseCamRotMat.m[3][0] = 0.0; inverseCamRotMat.m[3][1] = 0.0; inverseCamRotMat.m[3][2] =0.0; inverseCamRotMat.m[3][3] = 1.0;
	
	viewMatrix = inverseCamTranMat.operator*(inverseCamRotMat);
	return viewMatrix;
}

void Camera::MoveStraight(float delTime) {
	Vector3 delMove = -(cameraPos - targetPos).Normalize()*delTime*2.5;
	cameraPos += delMove;
	targetPos += delMove;
	//return *this;
}

void Camera::MoveSideWay(float delTime) {
	Vector3 delMove = cameraPos.Cross(upVector).Normalize()*delTime*2.5;
	cameraPos += delMove;
	targetPos += delMove;
}

void Camera::RotateAroundY(float delTime) {
	
	Vector4 localTarget = Vector4(0, 0, -(cameraPos - targetPos).Length(), 1);
	Matrix rotationaroundY;
	if (delTime*2.5f <= 80) {
		rotationaroundY.SetRotationY(delTime*2.5f);
		Vector4 localNewTarget = localTarget.operator*(rotationaroundY);
		Vector3 worldCamTransMatrix = Vector3(cameraPos.x, cameraPos.y, cameraPos.z);
		Matrix worldMatrix;
		worldMatrix.SetTranslation(worldCamTransMatrix);
		Vector4 im = localNewTarget.operator*(worldMatrix);
		targetPos.x = im.x;
		targetPos.y = im.y;
		targetPos.z = im.z;
	}
}
