#include "stdafx.h"
#include "NFG.h"
#include <stdio.h>
#include <iostream>
using namespace std; 

NFGData LoadNFG(char* modelfileName)	
	{
		FILE *f;
		if (fopen_s(&f, modelfileName, "r") != 0)
		{
			cout << "Failed to open the model file! " << endl;
			//return NULL;
		}

		char limit[50];
		int numVertices;
		int numIndices;
		float posX, posY, posZ;
		float normX, normY, normZ;
		float binormX, binormY, binormZ;
		float tgtX, tgtY, tgtZ;
		float uvX, uvY;
		int firstIndice, secondIndice, thirdIndice;

		fgets(limit, sizeof(limit), f);
		sscanf_s(limit, "NrVertices: %d", &numVertices);
		NFGData modelData;
		modelData.numVertices = numVertices;
		modelData.vertices = new Vertex[numVertices];
		//fseek(f, 0, SEEK_CUR);	
		int i = 0;
		while (!feof(f) && fscanf_s(f, "%*d . pos:[ %f , %f , %f ]; norm:[ %f , %f , %f ]; binorm:[ %f , %f , %f ]; tgt:[ %f , %f , %f ]; uv:[ %f , %f];", &posX, &posY, &posZ,
			&normX, &normY, &normZ,
			&binormX, &binormY, &binormZ,
			&tgtX, &tgtY, &tgtZ,
			&uvX, &uvY
		) != NULL && i< numVertices)
		{
			modelData.vertices[i].pos.x = posX; modelData.vertices[i].pos.y = posY; modelData.vertices[i].pos.z = posZ;
			modelData.vertices[i].normal.x = normX; modelData.vertices[i].normal.y = normY; modelData.vertices[i].normal.z = normZ;
			modelData.vertices[i].binormal.x = binormX; modelData.vertices[i].binormal.y = binormY; modelData.vertices[i].binormal.z = binormZ;
			modelData.vertices[i].tangent.x = tgtX; modelData.vertices[i].tangent.y = tgtY; modelData.vertices[i].tangent.z = tgtZ;
			modelData.vertices[i].uv.x = uvX; modelData.vertices[i].uv.y = uvY;
			i++;
		}
		fgets(limit, sizeof(limit), f);
		sscanf_s(limit, "NrIndices: %d", &numIndices);
		modelData.numIndices = numIndices;
		modelData.indice = new int[numIndices];
		int j = 0;
		do
		{
			fscanf_s(f, "%*d . %d , %d , %d", &firstIndice, &secondIndice, &thirdIndice);
			modelData.indice[j] = firstIndice;
			modelData.indice[j + 1] = secondIndice;
			modelData.indice[j + 2] = thirdIndice;
			j = j + 3;
		} while (!feof(f) && j<numIndices);

		fclose(f);
		return modelData;
	}

