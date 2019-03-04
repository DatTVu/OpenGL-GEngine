#pragma once
#include "Shaders.h"
#include "../Utilities/Mesh.h"
#include "../Utilities/TextureData.h"
#include <string>
using namespace std;

class Object
{	
private:
	Mesh m_objectMesh;
	TextureData m_objectText;
	Shaders* m_objectShader;
public:
	Object();
	~Object();
	void SetUpMesh(Mesh mesh);
	void SetUpTexture(TextureData texture);
	void SetUpShader(Shaders* shader);
	void Draw(Matrix mvp);
	///// Member data//////
	int m_ObjectID;
	int m_ObjectModelID;
	int m_ObjectTextCount;
	int* m_ObjectTextID;
	int m_ObjectCubeTextCount;
	int* m_ObjectCubeTextID;
	int m_ObjectShaderID;
	int m_ObjectLightCount;
	int* m_ObjectLightID;
	Vector3 m_ObjectPosition;
	Vector3 m_ObjectRotation;
	Vector3 m_ObjectScale;

};

