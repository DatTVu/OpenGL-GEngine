#pragma once
#include "utilities.h"
#include "../TrainingFramework/Vertex.h"
struct Texture {
	unsigned int id;
	char* type;
};
class ObjMesh
{
private:
	unsigned int VBO, IBO;
	int obj_numVertices;
	int obj_numIndices;
	void setupObjMesh();
	int get_NumVertices();
	int get_NumIndices();
public:
	//Constructor
	ObjMesh(Vertex* vertices, int* indices, Texture *textures);
	~ObjMesh();
	//members
	Vertex *obj_Vertices;
	int *obj_Indices;
	Texture *obj_Textures;
	


};

