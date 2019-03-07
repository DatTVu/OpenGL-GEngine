#pragma once
#include "CubeShaders.h"
#include "../Utilities/Mesh.h"
#include "CubeTexture.h"
#include <string>
using namespace std;

class CubeObject
{
private:
	Mesh m_objectMesh;
	CubeShaders* m_objectCubeShader;
public:
	CubeObject();
	~CubeObject();
	void SetUpCubeMesh(Mesh mesh);
	void SetUpCubeTexture(CubeTexture* texture);
	void SetUpCubeShader(CubeShaders* shader);
	void DrawCube(Matrix mvp);
	///////////////////////
	CubeTexture* m_objectCubeText;
	///// Member data//////
	int m_CubeObjectID;
	int m_CubeObjectModelID;
	int m_CubeObjectTextCount;
	int* m_CubeObjectTextID;
	int m_CubeObjectCubeTextCount;
	int* m_CubeObjectCubeTextID;
	int m_CubeObjectShaderID;
	int m_CubeObjectLightCount;
	int* m_CubeObjectLightID;
	Vector3 m_CubeObjectPosition;
	Vector3 m_CubeObjectRotation;
	Vector3 m_CubeObjectScale;

};