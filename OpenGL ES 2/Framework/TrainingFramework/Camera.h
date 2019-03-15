#pragma once
#include "../Utilities/utilities.h"
class Camera
{
	Vector3 cameraPos;
	Vector3 targetPos;
	Vector3 upVector;
	Matrix viewMatrix;
	Matrix worldMatrix;

	float aspectRatio;
	float initialAngle = 0.0f;
public:
	Camera(Vector3 worldCamPos, Vector3 worldTargetPos);
	~Camera();	
	Matrix CalculateViewMatrix();
	void CalculateWorlMatrixofCam();
	void MoveStraight(float delTime);
	void MoveSideWay(float delTime);
	void RotateAroundY(float delTime);
	void RotateAroundX(float delTime);
	Vector3 GetPos();
	Vector3 GetTargetPos();
};

