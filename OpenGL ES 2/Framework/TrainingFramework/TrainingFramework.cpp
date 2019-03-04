// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "CubeShaders.h"
#include "CubeTexture.h"
#include "Globals.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include <conio.h>
#include <iostream>

using namespace std;

const char k_resourceManagerPath[50] = "../Resources/ResourceManagerData.txt";
const char k_sceneManagerPath[50] = "../Resources/SceneManagerData.txt";
const char k_cubeTexturePath[75] = "../../ResourcesPacket/Textures/SkyboxTextures/";

GLuint cubeTextID;

Matrix WVP;
Matrix projectionMatrix;
Vector3 camWorld = Vector3(0.0, 0.0, 3.0);
Vector3 targetWorld = Vector3(0.0, 0.0, -1.0);
Camera camera1 = Camera(camWorld, targetWorld);
//Camera Movement
int upValue = 0;
int downValue = 0;
int leftValue = 0;
int rightValue = 0;

int turnLeft = 0;
int turnRight = 0;
int turnUp = 0;
int turnDown = 0;

////////TESTING//////////////////////////
CubeTexture cubeTexture;
CubeShaders cubeShader;
Vertex cubeVerticesData[8];
unsigned int cubevbo;
unsigned int cubeibo;



float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f, 1.0,
	-1.0f, -1.0f, -1.0f, 1.0,
	1.0f, -1.0f, -1.0f, 1.0,
	1.0f, -1.0f, -1.0f, 1.0,
	1.0f,  1.0f, -1.0f, 1.0,
	-1.0f,  1.0f, -1.0f, 1.0,

	-1.0f, -1.0f,  1.0f, 1.0,
	-1.0f, -1.0f, -1.0f, 1.0,
	-1.0f,  1.0f, -1.0f, 1.0,
	-1.0f,  1.0f, -1.0f, 1.0,
	-1.0f,  1.0f,  1.0f, 1.0,
	-1.0f, -1.0f,  1.0f, 1.0,

	1.0f, -1.0f, -1.0f, 1.0,
	1.0f, -1.0f,  1.0f, 1.0,
	1.0f,  1.0f,  1.0f, 1.0,
	1.0f,  1.0f,  1.0f, 1.0,
	1.0f,  1.0f, -1.0f, 1.0,
	1.0f, -1.0f, -1.0f, 1.0,

	-1.0f, -1.0f,  1.0f, 1.0,
	-1.0f,  1.0f,  1.0f, 1.0,
	1.0f,  1.0f,  1.0f, 1.0,
	1.0f,  1.0f,  1.0f, 1.0,
	1.0f, -1.0f,  1.0f, 1.0,
	-1.0f, -1.0f,  1.0f, 1.0,

	-1.0f,  1.0f, -1.0f, 1.0,
	1.0f,  1.0f, -1.0f, 1.0,
	1.0f,  1.0f,  1.0f, 1.0,
	1.0f,  1.0f,  1.0f, 1.0,
	-1.0f,  1.0f,  1.0f, 1.0,
	-1.0f,  1.0f, -1.0f, 1.0,

	-1.0f, -1.0f, -1.0f, 1.0,
	-1.0f, -1.0f,  1.0f, 1.0,
	1.0f, -1.0f, -1.0f, 1.0,
	1.0f, -1.0f, -1.0f, 1.0,
	-1.0f, -1.0f,  1.0f, 1.0,
	1.0f, -1.0f,  1.0f, 1.0
};

///////TESTING///////////////////////////

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );

	glEnable(GL_DEPTH_TEST);	

	projectionMatrix = projectionMatrix.SetPerspective((float)0.25*3.14, (float)(960/720), (float)0.4, (float)-1.0);

	ResourceManager::CreateInstance();

	ResourceManager::GetInstance()->LoadAndAllocateResourceData(k_resourceManagerPath);

	SceneManager::CreateInstance();

	SceneManager::GetInstance()->LoadAndAllocateSceneData(k_sceneManagerPath);
	
	SceneManager::GetInstance()->SetMeshPointerToRM(ResourceManager::GetInstance()->GetMeshData());

	SceneManager::GetInstance()->SetTextPointerToRM(ResourceManager::GetInstance()->GetTextureData());
		
	SceneManager::GetInstance()->SetShaderPointerToRM(ResourceManager::GetInstance()->GetShaderData());
	
	SceneManager::GetInstance()->SetUpMeshforObject();

	SceneManager::GetInstance()->SetUpTextureforObject();

	SceneManager::GetInstance()->SetUpShaderforObject();
	///////////////////
	cubeVerticesData[0].pos.x = 1.0f; cubeVerticesData[0].pos.y = -1.0f; cubeVerticesData[0].pos.z = -1.0f;
	cubeVerticesData[1].pos.x = 1.0f; cubeVerticesData[1].pos.y = -1.0f; cubeVerticesData[1].pos.z = 1.0f;
	cubeVerticesData[2].pos.x = 1.0f; cubeVerticesData[2].pos.y = 1.0f; cubeVerticesData[2].pos.z = 1.0f;
	cubeVerticesData[3].pos.x = 1.0f; cubeVerticesData[3].pos.y = 1.0f; cubeVerticesData[3].pos.z = -1.0f;
	cubeVerticesData[4].pos.x = -1.0f; cubeVerticesData[4].pos.y = 1.0f; cubeVerticesData[4].pos.z = 1.0f;
	cubeVerticesData[5].pos.x = -1.0f; cubeVerticesData[5].pos.y = -1.0f; cubeVerticesData[5].pos.z = 1.0f;
	cubeVerticesData[6].pos.x = -1.0f; cubeVerticesData[6].pos.y = 1.0f; cubeVerticesData[6].pos.z = -1.0f;
	cubeVerticesData[7].pos.x = -1.0f; cubeVerticesData[7].pos.y = -1.0f; cubeVerticesData[7].pos.z = -1.0f;

	glGenBuffers(1, &cubevbo);
	glBindBuffer(GL_ARRAY_BUFFER, cubevbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	cubeTexture = CubeTexture(k_cubeTexturePath);
	cubeShader.Init("../Resources/Shaders/CubeShaderVS.vs", "../Resources/Shaders/CubeShaderFS.fs");

	return 0;	
}

void Draw ( ESContext *esContext )
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	WVP = camera1.CalculateViewMatrix() * projectionMatrix;
	
	Matrix trans;
	trans.SetTranslation(0.0, 0.0, 0.0);
	WVP = trans * WVP;
	SceneManager::GetInstance()->Draw(WVP);

	Matrix scaleCubeMatrix;
	scaleCubeMatrix.SetScale(50.0, 50.0, 50.0);
	scaleCubeMatrix = scaleCubeMatrix * WVP;

	glUseProgram(cubeShader.program);

	glBindBuffer(GL_ARRAY_BUFFER, cubevbo);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeibo);
	
	int iCubeTextureLoc = glGetUniformLocation(cubeShader.program, "u_samplerCubeMap");
	glUniform1i(iCubeTextureLoc, 0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture.GetCubeTextID());

	glEnableVertexAttribArray(cubeShader.iPosVertexLoc);

	glVertexAttribPointer(cubeShader.iPosVertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glUniformMatrix4fv(cubeShader.iTransUniformLoc, 1, GL_FALSE, &scaleCubeMatrix.m[0][0]);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{	
	
	if (upValue)
	{
		camera1.MoveStraight(deltaTime);
		camera1.CalculateWorlMatrixofCam();
	}
	if (downValue)
	{
		camera1.MoveStraight(-deltaTime);
		camera1.CalculateWorlMatrixofCam();
	}
	if (leftValue)
	{
		camera1.MoveSideWay(deltaTime);
		camera1.CalculateWorlMatrixofCam();
	}
	if (rightValue)
	{
		camera1.MoveSideWay(-deltaTime);
		camera1.CalculateWorlMatrixofCam();
	}
	if (turnLeft)
	{
		
		camera1.RotateAroundY(deltaTime);
		camera1.CalculateWorlMatrixofCam();
	}
	if (turnRight)
	{
		camera1.RotateAroundY(-deltaTime);
		camera1.CalculateWorlMatrixofCam();
	}
	if (turnUp)
	{
		camera1.CalculateWorlMatrixofCam();
		camera1.RotateAroundX(deltaTime);
	}
	if (turnDown)
	{
		camera1.CalculateWorlMatrixofCam();
		camera1.RotateAroundX(-deltaTime);
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (key == VK_UP && bIsPressed == true)
	{
		upValue = 1;		
	}
	else if (key == VK_UP && bIsPressed == false)
	{
		upValue = 0;
	}
	if (key == VK_DOWN && bIsPressed == true)
	{
		downValue = 1;		
	}
	else if (key == VK_DOWN && bIsPressed == false)
	{
		downValue = 0;
	}
	if (key == VK_LEFT && bIsPressed == true)
	{
		leftValue = 1;		
	}
	else if (key == VK_LEFT &&bIsPressed == false)
	{
		leftValue = 0;
	}
	if (key == VK_RIGHT && bIsPressed == true)
	{
		rightValue = 1;		
	}
	else if (key == VK_RIGHT && bIsPressed == false)
	{
		rightValue = 0;
	}	

	if (key == VK_NUMPAD4 && bIsPressed == true)
	{
		turnLeft = 1;
	}
	else if (key == VK_NUMPAD4 && bIsPressed == false)
	{
		turnLeft = 0;
	}

	if (key == VK_NUMPAD6 && bIsPressed == true)
	{
		turnRight = 1;
	}
	else if (key == VK_NUMPAD6 && bIsPressed == false)
	{
		turnRight = 0;
	}

	if (key == VK_NUMPAD8 && bIsPressed == true)
	{
		turnUp = 1;
	}
	else if (key == VK_NUMPAD8 && bIsPressed == false)
	{
		turnUp = 0;
	}

	if (key == VK_NUMPAD2 && bIsPressed == true)
	{
		turnDown = 1;
	}
	else if (key == VK_NUMPAD2 && bIsPressed == false)
	{
		turnDown = 0;
	}
}

void CleanUp()
{
	//glDeleteBuffers(1, &vboId);
	//glDeleteBuffers(1, &iboId);
	//glDeleteTextures(1, &textId);	
	ResourceManager::DestroyInstance();
	SceneManager::DestroyInstance();	
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );	

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

