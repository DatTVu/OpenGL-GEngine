#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"

static void GenerateTriGrid(int numVertRows, int numVertCols, float dx, float dz, const Vector3& center, Vertex*& verts, int& numVerts, GLint*& indices, int& numIndices) {
	int numVertices = numVertRows*numVertCols;
	numVerts = numVertices;
	int numCellRows = numVertRows - 1;
	int numCellCols = numVertCols - 1;

	//total triangle will be generated
	int numTris = numCellRows*numCellCols * 2;

	float width = (float)numCellCols * dx;
	float depth = (float)numCellRows * dz;

	//===========================================
	// Build vertices.

	// We first build the grid geometry centered about the origin
	// and on the xz-plane, row by row and in a top-down fashion.
	// We then translate the grid vertices so that they are
	// centered about the specified parameter 'center'.

	verts = new Vertex[numVertices];

	//Offset to translate vertices to center
	float xOffset = width * -0.5f;
	float zOffset = depth * -0.5f;

	int k = 0;

	for (int i = 0; i < numVertRows; ++i)
	{
		for (int j = 0; j < numVertCols; ++j)
		{
			verts[k].pos.x = j * dx + xOffset;
			verts[k].pos.z = i * dz + zOffset;		//!** correct the calculation to fix with OpenGL - "i" instead of "-i"
			verts[k].pos.y = 0.0f;

			//calculate tex-coord
			verts[k].uv.x = (verts[k].pos.x + (0.5f*width)) / width;
			verts[k].uv.y = (verts[k].pos.z - (0.5f*depth)) / depth;	//!** correct the calculation to fix with OpenGL - "d" instead of "-d"

																		//translate to center
																		//To do later

			++k;
		}
	}
	//== build indices
	numIndices = numTris * 3;
	indices = new GLint[numIndices];

	k = 0;
 	for (int i = 0; i < numCellRows; ++i)
	{
		for (int j = 0; j < numCellCols; ++j)
		{
			indices[k] = i   * numVertCols + j;
			indices[k + 1] = i   * numVertCols + j + 1;
			indices[k + 2] = (i + 1) * numVertCols + j;

			indices[k + 3] = (i + 1) * numVertCols + j;
			indices[k + 4] = i   * numVertCols + j + 1;
			indices[k + 5] = (i + 1) * numVertCols + j + 1;

			// next quad
			k += 6;
		}
	}

}
