#pragma once
#include "../Utilities/utilities.h"
class LightSource
{
private:
	
public:
	LightSource();
	LightSource(Vector3 position, Vector3 color);
	~LightSource();
	int m_RmLightID;
	Vector3 m_lightPosition;
	Vector3 m_lightColor;
	Vector3 GetLightPosition();
	Vector3 GetLightColor();
};

