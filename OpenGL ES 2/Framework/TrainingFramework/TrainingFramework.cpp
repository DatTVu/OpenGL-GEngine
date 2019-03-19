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
#include "EffectsManager.h"

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
/*GLuint framebuffer;
GLuint colorTexId;
GLuint depthTexId;
unsigned int quadVBO;
unsigned int quadIBO;
Shaders quadShaders;
Shaders quadShaders2;
Shaders quadShaders3;
/////////////////////////
///Frame buffer object2//
GLuint framebuffer2;
GLuint colorTexId2;
GLuint depthTexId2;
/////////////////////////
///Frame buffer object3//
GLuint framebuffer3;
GLuint colorTexId3;
GLuint depthTexId3;
/////////////////////////
///Frame buffer object4//
GLuint framebuffer4;
GLuint colorTexId4;
GLuint depthTexId4;*/
////////////////////////
float farPlane = -1.0f;
float nearPlane = 0.4f;
float clarity = 8.0f;
float fadeuni = 10.0f;

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );	

	projectionMatrix = projectionMatrix.SetPerspective((float)0.25*3.14, (float)(960/720), nearPlane, farPlane);

	////////////////////////
	///Frame buffer object//
	/*glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &colorTexId);
	glBindTexture(GL_TEXTURE_2D, colorTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Globals::screenWidth, Globals::screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexId, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

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


	////////////////////////
	///Frame buffer object2//
	glGenFramebuffers(1, &framebuffer2);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer2);

	glGenTextures(1, &colorTexId2);
	glBindTexture(GL_TEXTURE_2D, colorTexId2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Globals::screenWidth, Globals::screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexId2, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &depthTexId2);
	glBindTexture(GL_TEXTURE_2D, depthTexId2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Globals::screenWidth, Globals::screenHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexId2, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {}
	else { cout << "Frame Buffer is not finished" << endl; }
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	////////////////////////
	///Frame buffer object3//
	glGenFramebuffers(1, &framebuffer3);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer3);

	glGenTextures(1, &colorTexId3);
	glBindTexture(GL_TEXTURE_2D, colorTexId3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Globals::screenWidth, Globals::screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexId3, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &depthTexId3);
	glBindTexture(GL_TEXTURE_2D, depthTexId3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Globals::screenWidth, Globals::screenHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexId3, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {}
	else { cout << "Frame Buffer is not finished" << endl; }
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	////////////////////////
	///Frame buffer object4//
	glGenFramebuffers(1, &framebuffer4);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer4);

	glGenTextures(1, &colorTexId4);
	glBindTexture(GL_TEXTURE_2D, colorTexId4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Globals::screenWidth, Globals::screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexId4, 0);	
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &depthTexId4);
	glBindTexture(GL_TEXTURE_2D, depthTexId4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Globals::screenWidth, Globals::screenHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexId4, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {}
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
	//quadShaders2.Init("../Resources/Shaders/PreBloomVS.vs", "../Resources/Shaders/PreBloomFS.fs");
	//quadShaders3.Init("../Resources/Shaders/PostBloomVS.vs", "../Resources/Shaders/PostBloomFS.fs");	
	quadShaders2.Init("../Resources/Shaders/PostDoFVS.vs", "../Resources/Shaders/PostDoFFS.fs");*/
	
	
	////////////////////////
	ResourceManager::CreateInstance();

	ResourceManager::GetInstance()->LoadAndAllocateResourceData(k_resourceManagerPath);

	SceneManager::CreateInstance();

	SceneManager::GetInstance()->LoadAndAllocateSceneData(k_sceneManagerPath);

	EffectsManager::CreateInstance();

	EffectsManager::GetInstance()->CreateQuad();

	EffectsManager::GetInstance()->LoadData("../Resources/EffectManagerData.txt");
	
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
	WVP = camera1.CalculateViewMatrix() * projectionMatrix;
	Matrix trans;
	trans.SetTranslation(0.0, 0.0, 0.0);
	WVP = trans * WVP;
	EffectsManager::GetInstance()->Draw(WVP, camera1.GetPos(), esContext);
	/*glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
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
	/////////////BLUR/////////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer2);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(quadShaders.program);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
	if (quadShaders.positionAttribute != -1)
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
	int blurPass1Tex = glGetUniformLocation(quadShaders.program, "u_Texture0");
	if (blurPass1Tex != -1)
	{
		glUniform1i(blurPass1Tex, 0);
	}
	unsigned int blurPass1Step;
	if ((blurPass1Step = glGetUniformLocation(quadShaders.program, "step")) != -1)
	{
		int k = 3;
		float x = 1.0f / esContext->width;
		float y = 1.0f / esContext->height;
		float z = sqrt(2.0f) / 2.0f * x;
		float w = sqrt(2.0f) / 2.0f * y;
		glUniform4f(blurPass1Step, k * x, k * y, k * z, k * w); 
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	////////////////////BLUR 2nd pass////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer3);	
	glUseProgram(quadShaders.program);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
	if (quadShaders.positionAttribute != -1)
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
	glBindTexture(GL_TEXTURE_2D, colorTexId2);
	int blurPass2Tex = glGetUniformLocation(quadShaders.program, "u_Texture0");
	if (blurPass2Tex != -1)
	{
		glUniform1i(blurPass2Tex, 0);
	}
	unsigned int blurPass2Step;
	if ((blurPass2Step = glGetUniformLocation(quadShaders.program, "step")) != -1)
	{
		int k = 5;
		float x = 1.0f / esContext->width;
		float y = 1.0f / esContext->height;
		float z = sqrt(2.0f) / 2.0f * x;
		float w = sqrt(2.0f) / 2.0f * y;
		glUniform4f(blurPass2Step, k * x, k * y, k * z, k * w);
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	////////////////////BLUR 3rd pass////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer4);	
	glUseProgram(quadShaders.program);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
	if (quadShaders.positionAttribute != -1)
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
	glBindTexture(GL_TEXTURE_2D, colorTexId3);
	int blurPass3Tex = glGetUniformLocation(quadShaders.program, "u_Texture0");
	if (blurPass3Tex != -1)
	{
		glUniform1i(blurPass3Tex, 0);
	}
	unsigned int blurPass3Step;
	if ((blurPass3Step = glGetUniformLocation(quadShaders.program, "step")) != -1)
	{
		int k = 9;
		float x = 1.0f / esContext->width;
		float y = 1.0f / esContext->height;
		float z = sqrt(2.0f) / 2.0f * x;
		float w = sqrt(2.0f) / 2.0f * y;
		glUniform4f(blurPass3Step, k * x, k * y, k * z, k * w);
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	/////////////////////////////////////////////////////
	///////////DOF///////////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(quadShaders2.program);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
	if (quadShaders2.positionAttribute != -1)
	{
		glEnableVertexAttribArray(quadShaders2.positionAttribute);
		glVertexAttribPointer(quadShaders2.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	}
	if (quadShaders2.textureAttribute != -1)
	{
		glEnableVertexAttribArray(quadShaders2.textureAttribute);
		glVertexAttribPointer(quadShaders2.textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos + sizenormal + sizebinormal + sizetangent);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexId);
	int originTexture = glGetUniformLocation(quadShaders2.program, "u_Texture0");
	if (originTexture != -1)
	{
		glUniform1i(originTexture, 0);
	}

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, colorTexId4);
	int blurredTex = glGetUniformLocation(quadShaders2.program, "u_Texture1");
	if (blurredTex != -1)
	{
		glUniform1f(blurredTex, 1);
	}

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, depthTexId);
	int depthTex = glGetUniformLocation(quadShaders2.program, "u_Texture2");
	if (depthTex != -1)
	{
		glUniform1i(depthTex, 2);
	}
	unsigned int DoFStep;
	if ((DoFStep = glGetUniformLocation(quadShaders2.program, "step")) != -1)
	{
		int k = 16;
		float x = 1.0f / esContext->width;
		float y = 1.0f / esContext->height;
		float z = sqrt(2.0f) / 2.0f * x;
		float w = sqrt(2.0f) / 2.0f * y;
		glUniform4f(DoFStep, k * x, k * y, k * z, k * w);
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);*/

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

