#pragma once
#include "Shaders.h"
#include "../Utilities/Mesh.h"
#include "../Utilities/TextureData.h"
#include "CubeTexture.h"
#include <string>
#include "LightSource.h"
using namespace std;

class Object
{	
private:
	Mesh m_objectMesh;	
	Shaders* m_objectShader;
public:
	Object();
	~Object();
	void SetUpMesh(Mesh mesh);
	void SetUpTexture(TextureData* texture);
	void SetUpCubeTexture(CubeTexture* texture);
	void SetUpShader(Shaders* shader);
	void SetUpLight(LightSource* light);
	void Draw(Matrix mvp, float time, Vector3 camPos);
	///////////////////////
	TextureData* m_objectText;
	CubeTexture * m_objectCubeText;
	LightSource *m_objectLight;
	///// Member data//////
	int m_ObjectID;
	int m_ObjectModelID;
	int m_ObjectTextCount;
	int* m_ObjectTextID;
	int m_ObjectCubeTextCount;
	int* m_ObjectCubeTextID;
	int m_ObjectLightCount;
	int* m_ObjectLightID;
	int m_ObjectShaderID;	
	Vector3 m_ObjectPosition;
	Vector3 m_ObjectRotation;
	Vector3 m_ObjectScale;
};

