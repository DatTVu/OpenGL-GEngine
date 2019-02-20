#pragma once
#include "../TrainingFramework/Vertex.h"
struct NFGData{
	Vertex *vertices = nullptr;
	int *indice = nullptr;
	int numVertices = 0;
	int numIndices = 0;
}
;

	NFGData LoadNFG(char* modelfileName);


