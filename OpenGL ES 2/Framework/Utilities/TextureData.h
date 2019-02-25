#pragma once
class TextureData
{
	int width, height, bpp;
	unsigned int textId;
	char* imageData;
	void SetUpTextureData(char* textPath);
public:
	TextureData(char* textPath);
	~TextureData();	
	unsigned int GetTextBufferID();

};

