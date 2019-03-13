#include "stdafx.h"
#include "Pass.h"


Pass::Pass()
{
}
Pass::Pass(int passID, int passShaderID, int passColorTextureCount, int *passColorTextureID, int passDepthTextureCount,
	int *passDepthTextureID, float passOtherData) {
	m_passID = passID;
	m_passShaderID = passShaderID;
	m_passColorTextureCount = passColorTextureCount;
	m_passColorTextureID = passColorTextureID;
	m_passDepthTextureCount = passDepthTextureCount;
	m_passDepthTextureID = passDepthTextureID;
	m_passOtherData= passOtherData;
}

Pass::~Pass()
{
}
