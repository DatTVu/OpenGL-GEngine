#include "stdafx.h"
#include "TextureData.h"
#include "../Utilities/utilities.h"
#include <iostream>

//using namespace std;
TextureData::TextureData() {

}

TextureData::TextureData(char* textPath)
{
	width = 0;
	height = 0;
	bpp = 0;
	imageData = nullptr;
	this->SetUpTextureData(textPath);
}


TextureData::~TextureData()
{	
}

void TextureData::SetUpTextureData(char* textPath) {
	glGenTextures(1, &textId);

	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textId);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	imageData = LoadTGA(textPath, &width, &height, &bpp);
	if (imageData)
	{
		if (bpp == 24) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (bpp == 32) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		std::cout << "Failed to load TGA file" << std::endl;
		return;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	delete(imageData);
	imageData = nullptr;
}

GLuint  TextureData::GetTextBufferID(){
	return textId;
}