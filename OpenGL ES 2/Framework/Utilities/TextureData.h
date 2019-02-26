#pragma once
class TextureData
{
	
	int width, height, bpp;
	unsigned int textId;
	char* imageData;
	void SetUpTextureData(char* textPath);
public:
	int RMTextID; //Texture ID read from config file by Resource Manager
	TextureData();
	TextureData(char* textPath);
	~TextureData();	
	unsigned int GetTextBufferID();

};

