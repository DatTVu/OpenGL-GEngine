#include "stdafx.h"
#include "LightSource.h"


LightSource::LightSource()
{
	m_lightColor = Vector3(0.0, 0.0, 0.0);
	m_lightPosition = Vector3(0.0, 0.0, 0.0);
}

LightSource::LightSource(Vector3 position, Vector3 color) {
	m_lightPosition = position;
	m_lightColor = color;
}
LightSource::~LightSource()
{
}
Vector3 LightSource::GetLightPosition() {
	return m_lightPosition;
}

Vector3 LightSource::GetLightColor(){
	return m_lightColor;
}
