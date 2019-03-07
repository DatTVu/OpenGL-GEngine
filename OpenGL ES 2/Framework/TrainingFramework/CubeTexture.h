#pragma once
class CubeTexture
{
	int m_width, m_height, m_bpp;
	unsigned int m_cubeTextId;
	char* m_cubePixel[6];
	void SetUpCubeTexture(const char* textPath);
public:
	int RMCubeTextID;
	CubeTexture();
	~CubeTexture();
	CubeTexture(const char* cubeTextPath);
	unsigned int GetCubeTextID();
};

