#pragma once
#include "utilities.h"
#include "../TrainingFramework/Vertex.h"


class Mesh
{	
	int m_numVertices;
	int m_numIndices;
	unsigned int vboId, iboId;
public:
	//Members
	Vertex* m_Vertices;
	int* m_Indices;
	//Constructor
	Mesh();
	//Destructor
	~Mesh();
	//Methods
	void SetUp(char*);
	void LoadVertexData(Mesh meshObject);
	unsigned int GetVboId();
	unsigned int GetIboId();
	int GetVerticesNum();
	int GetIndicesNum();
};
