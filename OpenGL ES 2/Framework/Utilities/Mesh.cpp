#include "stdafx.h"
#include "Mesh.h"
#include <stdio.h>
#include <iostream>
#include "../Utilities/utilities.h"

using namespace std;

Mesh::Mesh()
{
	Vertex* m_Vertices = nullptr;
	int* m_Indices = nullptr;
	int m_numVertices = 0;
	int m_numIndices = 0;
}

Mesh::Mesh(char* mfilename) {
	Vertex* m_Vertices = nullptr;
	int* m_Indices = nullptr;
	int m_numVertices = 0;
	int m_numIndices = 0;
	this->SetUp(mfilename);
	this->LoadVertexData(*this);
}

Mesh::~Mesh()
{

}

void Mesh::SetUp(char* modelPath) {

	FILE *f;
	if (fopen_s(&f, modelPath, "r") != 0)
	{
		cout << "Failed to open the model file! " << endl;
		return;
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
	//fseek(f, 0, SEEK_CUR);	
	m_numVertices = numVertices;
	m_Vertices = new Vertex[numVertices];
	int i = 0;
	while (!feof(f) && fscanf_s(f, "%*d . pos:[ %f , %f , %f ]; norm:[ %f , %f , %f ]; binorm:[ %f , %f , %f ]; tgt:[ %f , %f , %f ]; uv:[ %f , %f];", &posX, &posY, &posZ,
		&normX, &normY, &normZ,
		&binormX, &binormY, &binormZ,
		&tgtX, &tgtY, &tgtZ,
		&uvX, &uvY
	) != NULL && i < numVertices)
	{
		m_Vertices[i].pos.x = posX;	m_Vertices[i].pos.y = posY; m_Vertices[i].pos.z = posZ;
		m_Vertices[i].normal.x = normX; m_Vertices[i].normal.y = normY; m_Vertices[i].normal.z = normZ;
		m_Vertices[i].binormal.x = binormX; m_Vertices[i].binormal.y = binormY; m_Vertices[i].binormal.z = binormZ;
		m_Vertices[i].tangent.x = tgtX; m_Vertices[i].tangent.y = tgtY; m_Vertices[i].tangent.z = tgtZ;
		m_Vertices[i].uv.x = uvX; m_Vertices[i].uv.y = uvY;
		i++;
	}
	fgets(limit, sizeof(limit), f);
	sscanf_s(limit, "NrIndices: %d", &numIndices);
	m_numIndices = numIndices;
	m_Indices = new int[numIndices];
	int j = 0;
	do
	{
		fscanf_s(f, "%*d . %d , %d , %d", &firstIndice, &secondIndice, &thirdIndice);
		m_Indices[j] = firstIndice;
		m_Indices[j + 1] = secondIndice;
		m_Indices[j + 2] = thirdIndice;
		j = j + 3;
	} while (!feof(f) && j < numIndices);
	fclose(f);
	//delete(modelPath);
}

void Mesh::LoadVertexData(Mesh meshObject) {

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, meshObject.GetVerticesNum() * sizeof(Vertex), &meshObject.m_Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//index buffer object	 
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshObject.m_numIndices * sizeof(meshObject.m_Indices), meshObject.m_Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int Mesh::GetVerticesNum() {
	return m_numVertices;
}

int Mesh::GetIndicesNum() {
	return m_numIndices;
}

unsigned int Mesh::GetVboId() {
	return vboId;
}
unsigned int Mesh::GetIboId() {
	return iboId;
}