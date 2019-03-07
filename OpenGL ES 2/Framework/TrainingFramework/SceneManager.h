#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"

class SceneManager
{
private:
	////////////////////
	Object *m_SmObjectPointer;
	Mesh *m_SmObjectMeshPointer;
	TextureData *m_SmObject2DTexturePointer;
	Shaders* m_SmObjectShaderPointer;
	int m_SmObjectCount;
	float m_TimeUniform=0.0f;
	////////////////////	
protected:	
	SceneManager();
	~SceneManager();
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	SceneManager(const SceneManager &) {}
	SceneManager& operator =(const SceneManager &) {}

public:
	static void CreateInstance()
	{
		if (ms_SceneInstance == NULL)
			ms_SceneInstance = new SceneManager;
	}
	static SceneManager * GetInstance()
	{
		return ms_SceneInstance;
	}
	static void DestroyInstance()
	{
		if (ms_SceneInstance)
		{
			delete ms_SceneInstance;
			ms_SceneInstance = NULL;
		}
	}

	void LoadAndAllocateSceneData(const char* scenceManagerDataPath);
	void SetMeshPointerToRM(Mesh* SmMeshPointer);
	void SetTextPointerToRM(TextureData *SmObject2DTexturePointer);
	void SetShaderPointerToRM(Shaders* SmObjectShaderPointer);
	void SetUpMeshforObject();
	void SetUpTextureforObject();
	void SetUpShaderforObject();
	void Draw(Matrix mvp);
	void UpDateTimeUniform(float dtime);
	float GetTimeUniform();

protected:
	static SceneManager * ms_SceneInstance;
};
