#pragma once
#include <string>
#include "../Utilities/Mesh.h"
#include "../Utilities/TextureData.h"
#include "Shaders.h"
using namespace std;

class ResourceManager
{
private: 
	Mesh* m_RmMesh;	
	TextureData* m_RmTexture;
	Shaders* m_RmShaders;
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

	void LoadAndAllocateData();
	Mesh* GetMeshData();
	TextureData* GetTextureData();
	Shaders* GetShaderData();

protected:
	static ResourceManager * ms_pInstance;
};
