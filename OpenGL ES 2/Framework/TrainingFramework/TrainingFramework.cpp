// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>

using namespace std;
GLuint vboId, iboId;
GLuint textId; // create an id to store texture object
Shaders myShaders;
int numIndices;
//glm::mat4 trans = glm::mat4(1.0);
Matrix transMatrix;
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
float camSpeed = 1.0f;

int turnLeft = 0;
int turnRight = 0;
int turnUp = 0;
int turnDown = 0;

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);
	//Mesh Data
	Mesh womanMesh1;
	womanMesh1.SetUp("../../ResourcesPacket/Models/Woman2.nfg");
	womanMesh1.LoadVertexData(womanMesh1);
	vboId = womanMesh1.GetVboId();
	iboId = womanMesh1.GetIboId();
	numIndices = womanMesh1.GetIndicesNum();
	//Texture Data
	TextureData textureData;
	textureData.SetUpTextureData("../../ResourcesPacket/Textures/Woman2.tga");
	textId = textureData.GetTextBufferID();	
	
	//set up translational vector
	//trans = glm::translate(trans, glm::vec3(0.5, -1.0, 0.0));
	transMatrix.SetTranslation(0.5, -1.0, 0.0);
	projectionMatrix = projectionMatrix.SetPerspective((float)0.25*3.14, (float)(960/720), (float)0.4, (float)-1.0);
			
	//release resource
	delete(womanMesh1.m_Vertices);
	womanMesh1.m_Vertices = nullptr;
	delete(womanMesh1.m_Indices);
	womanMesh1.m_Indices = nullptr;
	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	              
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textId);

	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	}	
	if (myShaders.normalAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.normalAttribute);
		glVertexAttribPointer(myShaders.normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos);
	}
	if (myShaders.binormalAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.binormalAttribute);
		glVertexAttribPointer(myShaders.binormalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0+ sizepos + sizenormal);
	}
	if (myShaders.tangentAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.tangentAttribute);
		glVertexAttribPointer(myShaders.tangentAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos + sizenormal + sizebinormal);
	}
	if (myShaders.textureAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.textureAttribute);
		glVertexAttribPointer(myShaders.textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0+ sizepos + sizenormal + sizebinormal + sizetangent);
	}	

	//set up Uniform

	WVP = camera1.CalculateViewMatrix() * projectionMatrix;
	WVP = transMatrix * WVP;
	//texture uniform
	//int iTextureLoc = glGetUniformLocation(myShaders.program, "textID");
	//glUniform1i(iTextureLoc, 0);	
	//translation matrix uniform
	/*if (myShaders.translationUniform != -1)
	{
		glUniformMatrix4fv(myShaders.translationUniform, 1, GL_FALSE, glm::value_ptr(trans));
	}*/
	if (myShaders.translationUniform != -1)
	{
		glUniformMatrix4fv(myShaders.translationUniform, 1, GL_FALSE, &WVP.m[0][0]);
	}
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{	
	float speed = camSpeed* deltaTime;
	if (upValue)
	{
		camera1.MoveStraight(speed);
		camera1.CalculateWorlMatrixofCam();
	}
	if (downValue)
	{
		camera1.MoveStraight(-speed);
		camera1.CalculateWorlMatrixofCam();
	}
	if (leftValue)
	{
		camera1.MoveSideWay(speed);
		camera1.CalculateWorlMatrixofCam();
	}
	if (rightValue)
	{
		camera1.MoveSideWay(-speed);
		camera1.CalculateWorlMatrixofCam();
	}
	if (turnLeft)
	{
		camera1.CalculateWorlMatrixofCam();
		camera1.RotateAroundY(speed);
	}
	if (turnRight)
	{
		camera1.CalculateWorlMatrixofCam();
		camera1.RotateAroundY(-speed);
	}
	if (turnUp)
	{
		camera1.CalculateWorlMatrixofCam();
		camera1.RotateAroundX(speed);
	}
	if (turnDown)
	{
		camera1.CalculateWorlMatrixofCam();
		camera1.RotateAroundX(-speed);
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (key == VK_UP && bIsPressed == true)
	{
		upValue = 1;
		//camera1.MoveStraight(0.05);
	}
	else if (key == VK_UP && bIsPressed == false)
	{
		upValue = 0;
	}
	if (key == VK_DOWN && bIsPressed == true)
	{
		downValue = 1 << 1;
		//.MoveStraight(-0.05);
	}
	else if (key == VK_DOWN && bIsPressed == false)
	{
		downValue = 0;
	}
	if (key == VK_LEFT && bIsPressed == true)
	{
		leftValue = 1 << 2;
		//.MoveStraight(-0.05);
	}
	else if (key == VK_LEFT &&bIsPressed == false)
	{
		leftValue = 0;
	}
	if (key == VK_RIGHT && bIsPressed == true)
	{
		rightValue = 1 << 3;
		//.MoveStraight(-0.05);
	}
	else if (key == VK_RIGHT && bIsPressed == false)
	{
		rightValue = 0;
	}	

	if (key == VK_NUMPAD4 && bIsPressed == true)
	{
		turnLeft = 1 << 4;
	}
	else if (key == VK_NUMPAD4 && bIsPressed == false)
	{
		turnLeft = 0;
	}

	if (key == VK_NUMPAD6 && bIsPressed == true)
	{
		turnRight = 1 << 5;
	}
	else if (key == VK_NUMPAD6 && bIsPressed == false)
	{
		turnRight = 0;
	}

	if (key == VK_NUMPAD8 && bIsPressed == true)
	{
		turnUp = 1 << 6;
	}
	else if (key == VK_NUMPAD8 && bIsPressed == false)
	{
		turnUp = 0;
	}

	if (key == VK_NUMPAD2 && bIsPressed == true)
	{
		turnDown = 1 << 7;
	}
	else if (key == VK_NUMPAD2 && bIsPressed == false)
	{
		turnDown = 0;
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
	glDeleteTextures(1, &textId);
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
