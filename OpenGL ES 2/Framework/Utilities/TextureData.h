#pragma once
class TextureData
{
	int width, height, bpp;
	unsigned int textId;
	char* imageData;
public:
	TextureData();
	~TextureData();
	void SetUpTextureData(char* textPath);
	unsigned int GetTextBufferID();

};

