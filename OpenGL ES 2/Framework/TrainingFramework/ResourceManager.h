#pragma once

#include <string>
using namespace std;
class ResourceManager
{
private: 
	int *modelID, *texture2D_ID, *cubeTexture, *shaderID;
	string *modelPath, *texture2DPath, *cubeTexturePath, *shaderPath;
	
protected:
	ResourceManager();
	~ResourceManager();
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	ResourceManager(const ResourceManager &) {}
	ResourceManager& operator =(const ResourceManager &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new ResourceManager;
	}
	static ResourceManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}

	void LoadData();

protected:
	static ResourceManager * ms_pInstance;
};
//...