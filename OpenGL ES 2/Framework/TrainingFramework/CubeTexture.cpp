#include "stdafx.h"
#include "CubeTexture.h"
#include "../Utilities/utilities.h"
#include <iostream>
using namespace std;
CubeTexture::CubeTexture()
{
}


CubeTexture::~CubeTexture()
{
}

CubeTexture::CubeTexture(const char* cubeTextPath) {
	m_width = 0;
	m_height = 0;
	m_bpp = 0;	
	for (int i = 0; i < 6; i++)
	{
		m_cubePixel[i] = nullptr;
	}
	this->SetUpCubeTexture(cubeTextPath);
}

void CubeTexture::SetUpCubeTexture(const char* cubeTextPath) {

	glGenTextures(1, &m_cubeTextId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeTextId);	
	char prePath[100];	
	char* postPath[6] = {"right.tga", "left.tga", "top.tga", "bottom.tga", "back.tga", "front.tga"};
	for (int i = 0; i < 6; i++) {
		strcpy(prePath, cubeTextPath);
		strcat(prePath, postPath[i]);
		m_cubePixel[i] = LoadTGA(prePath, &m_width, &m_height, &m_bpp);
		if (m_bpp == 24) {
			if (m_cubePixel[i])
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_cubePixel[i]);
			}
			else
			{
				cout << "Failed to load Cube TGA texture: " << i << endl;
				return;
			}
		}
		else if (m_bpp == 32) {
			if (m_cubePixel[i])
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_cubePixel[i]);
			}
			else
			{
				cout << "Failed to load Cube TGA texture: " << i << endl;
				return;
			}
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
	/*for (int i = 0; i < 6; i++) {
		delete m_cubePixel[i];
		m_cubePixel[i] = nullptr;				
	}*/
	

}

GLuint CubeTexture::GetCubeTextID() {
	return m_cubeTextId;
}
