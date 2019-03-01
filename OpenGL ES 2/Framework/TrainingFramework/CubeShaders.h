#pragma once
#include "../Utilities/utilities.h"
class CubeShaders
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint iPosVertexLoc;
	GLuint iTransUniformLoc;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~CubeShaders();
};

