#include "stdafx.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "Heightmap.h"
#include "TriangleGrid.h"
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
		char type[10];
		fgets(limit, sizeof(limit), resourceFile);
		sscanf_s(limit, "TYPE %s", &type, 10);
		//if (type == "NFG") {
		if (strcmp(type, "NFG") == 0) {
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
		else if (strcmp(type,"RAW") == 0) {
			Heightmap heightmap;
			int terrainRow;
			int terrainColumn;
			float heightScale;
			float heightOffset;
			float deltaxTerrain;
			float deltazTerrain;
			Vector3 terrainCenter;
			Vertex* terrainVertices;
			int terrainVertexCount;
			int* terrainIndice;
			int terrainIndiceCount;
			fgets(limit, sizeof(limit), resourceFile);
			sscanf_s(limit, "ID %d", &m_RmMesh[i].m_RManagerID);
			fgets(limit, sizeof(limit), resourceFile);
			sscanf_s(limit, "row %d", &terrainRow);
			fgets(limit, sizeof(limit), resourceFile);
			sscanf_s(limit, "column %d", &terrainColumn);
			fgets(limit, sizeof(limit), resourceFile);
			sscanf_s(limit, "heightScale %f", &heightScale);
			fgets(limit, sizeof(limit), resourceFile);
			sscanf_s(limit, "heightOffset %f", &heightOffset);
			fgets(limit, sizeof(limit), resourceFile);
			sscanf_s(limit, "deltaX %f", &deltaxTerrain);
			fgets(limit, sizeof(limit), resourceFile);
			sscanf_s(limit, "deltaZ %f", &deltazTerrain);
			heightmap.loadRAW(terrainRow, terrainColumn, "../../ResourcesPacket/Textures/heightmap.raw", heightScale, heightOffset);
			GenerateTriGrid(terrainRow, terrainColumn, deltaxTerrain, deltazTerrain, terrainCenter, terrainVertices, terrainVertexCount, terrainIndice, terrainIndiceCount);
			for (int i = 0; i < terrainRow; i++) {
				for (int j = 0; j < terrainColumn; j++) {
					int index = i* terrainColumn + j;
					terrainVertices[index].pos.y = heightmap(i, j) / 25;
				}
			}
			m_RmMesh[i] = Mesh(terrainVertices, terrainIndice, terrainVertexCount, terrainIndiceCount);
			i++;
		}
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
	sscanf_s(limit, "#Cube Textures: %d", &count);
	m_RmCubeTexture = new CubeTexture[count];
	while (!feof(resourceFile) && i < count) {
		char fakepath[100];
		char path[100] = "../../ResourcesPacket/";
		fgets(limit, sizeof(limit), resourceFile);
		sscanf_s(limit, "ID %d", &m_RmCubeTexture[i].RMCubeTextID);
		fgets(limit, sizeof(limit), resourceFile);
		sscanf(limit, "FILE %s", &fakepath, 100);
		strcat(path, fakepath);
		cout << path << endl;
		fgets(limit, sizeof(limit), resourceFile);
		m_RmCubeTexture[i] = CubeTexture(path);
		i++;
	}
	i = 0;
	fseek(resourceFile, 2, SEEK_CUR);
	/////////////////////////////
	////Read the Shaders data////
	/////////////////////////////
	fgets(limit, sizeof(limit), resourceFile);
	sscanf_s(limit, "#Shaders: %d", &count); //count of shaders
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
	i = 0;
	fseek(resourceFile, 2, SEEK_CUR);
	///////////////////////////////
	///////READ LIGHT DATA/////////
	///////////////////////////////
	fgets(limit, sizeof(limit), resourceFile);
	sscanf_s(limit, "#LIGHTS: %d", &count); //count of light
	m_RmLightSource = new LightSource[count];
	while (!feof(resourceFile) && i < count) {		
		fgets(limit, sizeof(limit), resourceFile);
		sscanf_s(limit, "ID %d", &m_RmLightSource[i].m_RmLightID);
		fgets(limit, sizeof(limit), resourceFile);
		sscanf_s(limit, "POSITION %f, %f, %f", &m_RmLightSource[i].m_lightPosition.x, &m_RmLightSource[i].m_lightPosition.y, &m_RmLightSource[i].m_lightPosition.z);
		fgets(limit, sizeof(limit), resourceFile);
		sscanf_s(limit, "COLOR %f, %f, %f", &m_RmLightSource[i].m_lightColor.x, &m_RmLightSource[i].m_lightColor.y, &m_RmLightSource[i].m_lightColor.z);	
	}
	i = 0;
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
CubeTexture* ResourceManager::GetCubeTextureData() {
	return m_RmCubeTexture;
}
LightSource* ResourceManager::GetLightData(){
	return m_RmLightSource;
}
