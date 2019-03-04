#include "stdafx.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

ResourceManager * ResourceManager::ms_pInstance = NULL;

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {

	for (int i = 0; i < sizeof(m_RmMesh) / sizeof(Mesh); i++) {
		delete[] m_RmMesh[i].m_Vertices;
		m_RmMesh[i].m_Vertices = nullptr;
		delete[] m_RmMesh[i].m_Indices;
		m_RmMesh[i].m_Indices = nullptr;
	}	
	delete[] m_RmMesh;
	m_RmMesh = nullptr;
	delete[] m_RmShaders;
	m_RmShaders = nullptr;
	delete[] m_RmTexture;
	m_RmTexture = nullptr;	
	
}

void ResourceManager::LoadAndAllocateResourceData(const char* resourceManagerPath) {
	
	FILE* resourceFile;
	if (fopen_s(&resourceFile, resourceManagerPath, "r") != 0)
	//if (fopen_s(&resourceFile, "../Resources/ResourceManagerData.txt", "r") != 0)
	{
		cout << " Failed to open Resource Manager Data file" << endl;
		return;
	}

	/////////////////////////
	char limit[50];
	int count;
	/////////////////////////////
	////Read the model data//////
	/////////////////////////////
	fgets(limit, sizeof(limit), resourceFile); 
	sscanf_s(limit, "#Models: %d", &count);	//count of models
	m_RmMesh = new Mesh[count]; //allocate an array of Mesh

	int i = 0;
		
 	while (!feof(resourceFile) && i<count) {
		char fakepath[100];
		char path[100] = "../../ResourcesPacket/";
		fgets(limit, sizeof(limit), resourceFile);
		sscanf_s(limit, "ID %d", &m_RmMesh[i].m_RManagerID);
		fgets(limit, sizeof(limit), resourceFile);
		sscanf(limit, "FILE %s", &fakepath, 100);		
		strcat(path, fakepath);		
		cout << path << endl;
		m_RmMesh[i] = Mesh(path);
		i++;	
	}
	i = 0;

	//Move the cursore to the line where texture data is located
	fseek(resourceFile, 2, SEEK_CUR);	

	/////////////////////////////
	////Read the 2d texture data/
	/////////////////////////////
	fgets(limit, sizeof(limit), resourceFile); 
	sscanf_s(limit, "#2D Textures: %d", &count); //count of texture
	m_RmTexture = new TextureData[count];
		
	while (!feof(resourceFile) && i < count) {
		char fakepath[100];
		char path[100] = "../../ResourcesPacket/";
		fgets(limit, sizeof(limit), resourceFile);
		sscanf_s(limit, "ID %d", &m_RmTexture[i].RMTextID);
		fgets(limit, sizeof(limit), resourceFile);
		sscanf(limit, "FILE %s", &fakepath, 100);
		strcat(path, fakepath);
		cout << path << endl;
		fgets(limit, sizeof(limit), resourceFile);
		m_RmTexture[i] = TextureData(path);
		i++;
	}

	i = 0;
	fseek(resourceFile, 2, SEEK_CUR); //skip reading Cube Texture	
	fgets(limit, sizeof(limit), resourceFile);
	fseek(resourceFile, 2, SEEK_CUR);
	/////////////////////////////
	////Read the Shaders data////
	/////////////////////////////
	fgets(limit, sizeof(limit), resourceFile);
	sscanf_s(limit, "#Shaders: %d", &count); //count of texture
	m_RmShaders = new Shaders[count];

	while (!feof(resourceFile) && i < count) {
		char fakepath[100];
		char vspath[100] = "../Resources/";
		char fakepath2[100];
		char fspath[100] = "../Resources/";

		fgets(limit, sizeof(limit), resourceFile);
		sscanf_s(limit, "ID %d", &m_RmShaders[i].m_RmShaderID);

		fgets(limit, sizeof(limit), resourceFile);
		sscanf(limit, "VS %s", &fakepath, 100);
		strcat(vspath, fakepath);
		cout << vspath << endl;
		
		fgets(limit, sizeof(limit), resourceFile);
		sscanf(limit, "FS %s", &fakepath2, 100);
		strcat(fspath, fakepath2);
		cout << fspath << endl;
		m_RmShaders[i].Init(vspath, fspath);

		strcpy(m_RmShaders[i].fileVS, vspath);
		strcpy(m_RmShaders[i].fileFS, fspath);		
		
		fgets(limit, sizeof(limit), resourceFile);
		fgets(limit, sizeof(limit), resourceFile);
		fgets(limit, sizeof(limit), resourceFile);		
		i++;
	}	
	fclose(resourceFile);		
}


Mesh* ResourceManager::GetMeshData()
{
	return m_RmMesh;
}
TextureData* ResourceManager::GetTextureData() {
	return m_RmTexture;
}
Shaders* ResourceManager::GetShaderData() {
	return m_RmShaders;
}
