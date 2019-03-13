#pragma once
#include "../Utilities/utilities.h"
#include "Shaders.h"
#include "Effects.h"
class EffectsManager
{
private:
	GLuint *m_framebufferID;
	GLuint *m_colorTexID;
	GLuint *m_depthTexID;
	unsigned int m_quadVBO;
	unsigned int m_quadIBO;
	Shaders *m_effectShaders;
protected:
	Effects* m_EmEffect;
	EffectsManager() {}
	~EffectsManager() {}
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	EffectsManager(const EffectsManager &) {}
	EffectsManager& operator =(const EffectsManager &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new EffectsManager;
	}
	static EffectsManager * GetInstance()
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

	void CreateQuad();
	void LoadData(const char* effectManagerPath);
	

protected:
	static EffectsManager * ms_pInstance;
};
//...