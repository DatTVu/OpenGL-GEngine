#include "stdafx.h"
#include "ObjMesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ObjMesh::ObjMesh(Vertex* vertices, int* indices, Texture *textures)
{
	this->obj_Vertices = vertices;
	this->obj_Indices = indices;
	this->obj_Textures = textures;
	setupObjMesh();
}

void ObjMesh::setupObjMesh() {
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->get_NumVertices() * sizeof(Vertex), &obj_Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->get_NumIndices() * sizeof(obj_Indices), obj_Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int ObjMesh::get_NumIndices(){
	return obj_numIndices;
}

int ObjMesh::get_NumVertices() {
	return obj_numVertices;
}


ObjMesh::~ObjMesh()
{
}
