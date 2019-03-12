// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "CubeTexture.h"
#include "Globals.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "TriangleGrid.h"
#include <conio.h>
#include <iostream>
#include "Heightmap.h"

using namespace std;

const char k_resourceManagerPath[50] = "../Resources/ResourceManagerData.txt";
const char k_sceneManagerPath[50] = "../Resources/SceneManagerData.txt";

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
////////////////////////
///Frame buffer object//
GLuint framebuffer;
GLuint colorTexId;
GLuint depthTexId;
unsigned int quadVBO;
unsigned int quadIBO;
#define COLOR_TEXTURE 0
#define DEPTH_TEXTURE 1
Shaders quadShaders;
////////////////////////

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );	

	projectionMatrix = projectionMatrix.SetPerspective((float)0.25*3.14, (float)(960/720), (float)0.4, (float)-1.0);

	////////////////////////
	///Frame buffer object//
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &colorTexId);
	glBindTexture(GL_TEXTURE_2D, colorTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Globals::screenWidth, Globals::screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexId, 0);

	glGenTextures(1, &depthTexId);
	glBindTexture(GL_TEXTURE_2D, depthTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Globals::screenWidth, Globals::screenHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexId, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){}
	else { cout << "Frame Buffer is not finished" << endl; }
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Vertex quadVertices[4];
	quadVertices[0].pos.x =  1.0f;  quadVertices[0].pos.y =  1.0f;  quadVertices[0].pos.z = 0.0f;
	quadVertices[1].pos.x =  1.0f;  quadVertices[1].pos.y = -1.0f;  quadVertices[1].pos.z = 0.0f;
	quadVertices[2].pos.x = -1.0f;  quadVertices[2].pos.y = -1.0f;  quadVertices[2].pos.z = 0.0f;
	quadVertices[3].pos.x = -1.0f;	quadVertices[3].pos.y =  1.0f;	quadVertices[3].pos.z = 0.0f;
	quadVertices[0].uv.x =  1.0f;  quadVertices[0].uv.y = 1.0f;
	quadVertices[1].uv.x =  1.0f;  quadVertices[1].uv.y = 0.0f;
	quadVertices[2].uv.x =  0.0f;  quadVertices[2].uv.y = 0.0f;
	quadVertices[3].uv.x =  0.0f;  quadVertices[3].uv.y = 1.0f;
	//index data
	unsigned int idx[] = { 0, 1, 2, 0, 2, 3 };


    glGenBuffers(1, &quadVBO);    
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &quadIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//quadShaders.Init("../Resources/Shaders/FrameBufferVS.vs", "../Resources/Shaders/FrameBufferFS.fs");
	//quadShaders.Init("../Resources/Shaders/BlackWhiteVS.vs", "../Resources/Shaders/BlackWhiteFS.fs");
	quadShaders.Init("../Resources/Shaders/BlurEffectVS.vs", "../Resources/Shaders/BlurEffectFS.fs");
	
	
	////////////////////////
	ResourceManager::CreateInstance();

	ResourceManager::GetInstance()->LoadAndAllocateResourceData(k_resourceManagerPath);

	SceneManager::CreateInstance();

	SceneManager::GetInstance()->LoadAndAllocateSceneData(k_sceneManagerPath);
	
	SceneManager::GetInstance()->SetMeshPointerToRM(ResourceManager::GetInstance()->GetMeshData());

	SceneManager::GetInstance()->SetTextPointerToRM(ResourceManager::GetInstance()->GetTextureData(), ResourceManager::GetInstance()->GetCubeTextureData());
		
	SceneManager::GetInstance()->SetShaderPointerToRM(ResourceManager::GetInstance()->GetShaderData());

	SceneManager::GetInstance()->SetLightPointerToRM(ResourceManager::GetInstance()->GetLightData());
	
	SceneManager::GetInstance()->SetUpMeshforObject();

	SceneManager::GetInstance()->SetUpTextureforObject();

	SceneManager::GetInstance()->SetUpShaderforObject();

	SceneManager::GetInstance()->SetUpLightforObject();

	return 0;
}

void Draw ( ESContext *esContext )
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	WVP = camera1.CalculateViewMatrix() * projectionMatrix;
	Matrix trans;
	trans.SetTranslation(0.0, 0.0, 0.0);
	WVP = trans * WVP;
	SceneManager::GetInstance()->Draw(WVP, camera1.GetPos());
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(quadShaders.program);	
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
	if(quadShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(quadShaders.positionAttribute);
		glVertexAttribPointer(quadShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	}
	if (quadShaders.textureAttribute != -1)
	{
		glEnableVertexAttribArray(quadShaders.textureAttribute);
		glVertexAttribPointer(quadShaders.textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos + sizenormal + sizebinormal + sizetangent);
	}	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexId);
	int iTextureLoc = glGetUniformLocation(quadShaders.program, "u_Texture0");
	if (iTextureLoc != -1)
	{
		glUniform1i(iTextureLoc, 0);
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{	
	SceneManager::GetInstance()->UpDateTimeUniform(deltaTime);

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

