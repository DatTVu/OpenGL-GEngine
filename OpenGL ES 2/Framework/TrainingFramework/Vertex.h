#pragma once
#include "Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 normal;
	Vector3 binormal;
	Vector3 tangent;	
	Vector2 uv;
};

#define sizepos sizeof(Vector3)
#define sizenormal  sizeof(Vector3)
#define sizebinormal sizeof(Vector3)
#define sizetangent sizeof(Vector3)
#define sizeuv sizeof(Vector2)