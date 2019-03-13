#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint normalAttribute;
	GLint binormalAttribute;
	GLint tangentAttribute;
	GLint textureAttribute;
	GLuint wvpUniform;
	GLuint worldMatUniform;
	GLuint cameraPosUniform;
	GLuint textureUniform0;
	GLuint textureUniform1;
	GLuint textureUniform2;
	GLuint textureUniform3;
	GLuint textureUniform4;
	GLuint cubeTextureUniform0;
	GLuint timeUniform;
	GLuint lightPosUniform0;
	GLuint lightColorUniform0;
	GLuint lightPosUniform1;
	GLuint lightColorUniform1;
	GLuint lightPosUniform2;
	GLuint lightColorUniform2;
	GLuint stepUniform;
	int m_RmShaderID;
	int m_EmShaderID;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	Shaders();	
	~Shaders();
};