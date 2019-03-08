#pragma once
#include "../TrainingFramework/Vertex.h"


class Mesh
{	
private:
	int m_numVertices;
	int m_numIndices;
	unsigned int vboId, iboId;
	void SetUp(char* modelPath);
	void LoadVertexData(Mesh meshObject);
public:
	//Members	
	Vertex* m_Vertices;
	int* m_Indices;
	//Constructor
	Mesh();
	Mesh(char* mfilename);
	Mesh(Vertex* vertex, int* indices, int numVertices, int numIndices);
	//Destructor
	~Mesh();
	//Methods	
	unsigned int GetVboId();
	unsigned int GetIboId();
	int m_RManagerID; // Mesh ID read from a config file by Resouce Manager
	int GetVerticesNum();
	int GetIndicesNum();
};
