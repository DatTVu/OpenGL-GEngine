#pragma once
class Pass
{
public:
	int m_passID;
	int m_passShaderID;
	int m_passColorTextureCount;
	int *m_passColorTextureID;
	int m_passDepthTextureCount;
	int *m_passDepthTextureID;
	float m_passOtherData;
	int m_passTarget;
	Pass();
	Pass(int passID, int passShaderID, int passColorTextureCount, int *passColorTextureID, int passDepthTextureCount,
	int *passDepthTextureID, float passOtherData);
	~Pass();
};

