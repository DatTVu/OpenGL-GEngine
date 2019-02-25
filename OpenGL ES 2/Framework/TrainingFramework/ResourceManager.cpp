#include "stdafx.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
ResourceManager * ResourceManager::ms_pInstance = NULL;
//...
//...
#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	modelID = nullptr;	
	texture2D_ID = nullptr;
	shaderID = nullptr;
}

ResourceManager::~ResourceManager() {

}


void ResourceManager::LoadData() {
	FILE* resourceFile;
	if (fopen_s(&resourceFile, "../Resources/ResourceManagerData.txt", "r") != 0)
	{
		cout << " Failed to open Resource Manager Data file" << endl;
		return;
	}

	char limit[50];
	int numModels;
	int num2dTextures;
	int numCubeTextures;
	int numShaders;

	fgets(limit, sizeof(limit), resourceFile);
	sscanf_s(limit, "#Models: %d", &numModels);
	modelID = new int[numModels];
	modelPath = new string[numModels];
	int ID = 0;
	char Path[50];
	int i = 0;

	while (!feof(resourceFile) && i<numModels) {
		fgets(limit, sizeof(limit), resourceFile);
		sscanf_s(limit, "ID %d", &ID);
		modelID[i] = ID;
		fgets(limit, sizeof(limit), resourceFile);
		sscanf(limit, "FILE %s", Path, 50);
		modelPath[i] = Path;
		cout << "Model: " << i << " ID " << modelID[i] << endl;
		cout << "Model: " << i << " path " <<modelPath[i] << endl;	
		i++;
	}

	i = 0;
	
	fclose(resourceFile);	

}

