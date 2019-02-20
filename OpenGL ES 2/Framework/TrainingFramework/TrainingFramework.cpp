// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
GLuint vboId, iboId;
GLuint textId; // create an id to store texture object
Shaders myShaders;
int numIndices;
glm::mat4 trans = glm::mat4(1.0);

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
	trans = glm::translate(trans, glm::vec3(0.5, -1.0, 0.0));
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
	//texture uniform
	//int iTextureLoc = glGetUniformLocation(myShaders.program, "textID");
	//glUniform1i(iTextureLoc, 0);	
	//translation matrix uniform
	if (myShaders.translationUniform != -1)
	{
		glUniformMatrix4fv(myShaders.translationUniform, 1, GL_FALSE, glm::value_ptr(trans));
	}
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	trans = glm::rotate(trans, (float)deltaTime, glm::vec3(0.0, 1.0, 0.0));
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (key == VK_UP)
	trans = glm::translate(trans, glm::vec3(0.0, 0.05, 0.0));
	if(key == VK_DOWN)
	trans = glm::translate(trans, glm::vec3(0.0, -0.05, 0.0));
	if (key == VK_LEFT)
	trans = glm::translate(trans, glm::vec3(-0.05, 0.0, 0.0));
	if (key == VK_RIGHT)
	trans = glm::translate(trans, glm::vec3(0.05, 0.0, 0.0));
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

