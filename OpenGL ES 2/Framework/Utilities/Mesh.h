#pragma once
#include "utilities.h"
#include "../TrainingFramework/Vertex.h"


class Mesh
{	
private:
	int m_numVertices;
	int m_numIndices;
	unsigned int vboId, iboId;
	void SetUp(char*);
	void LoadVertexData(Mesh meshObject);
public:
	//Members
	Vertex* m_Vertices;
	int* m_Indices;
	//Constructor
	Mesh();
	Mesh(char* mfilename);
	//Destructor
	~Mesh();
	//Methods	
	unsigned int GetVboId();
	unsigned int GetIboId();
	int GetVerticesNum();
	int GetIndicesNum();
};
