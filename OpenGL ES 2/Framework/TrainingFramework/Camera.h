#pragma once
#include "../Utilities/utilities.h"
class Camera
{
	Vector3 cameraPos;
	Vector3 targetPos;
	Vector3 upVector;
	Matrix viewMatrix;
	float aspectRatio;
public:
	Camera(Vector3 worldCamPos, Vector3 worldTargetPos);
	~Camera();	
	Matrix CalculateViewMatrix();	
	void MoveStraight(float delTime);
	void MoveSideWay(float delTime);
	void RotateAroundY(float delTime);
};

