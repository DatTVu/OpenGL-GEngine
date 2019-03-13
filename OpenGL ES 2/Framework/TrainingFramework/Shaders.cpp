#include "stdafx.h"
#include "Shaders.h"

Shaders::Shaders() {

}

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	normalAttribute = glGetAttribLocation(program, "a_normal");
	binormalAttribute = glGetAttribLocation(program, "a_binormal");
	tangentAttribute = glGetAttribLocation(program, "a_tangent");
	textureAttribute = glGetAttribLocation(program, "a_texCoord");
	//finding location of uniforms 
	wvpUniform = glGetUniformLocation(program, "u_WVP");
	worldMatUniform = glGetUniformLocation(program, "u_W");
	textureUniform0 = glGetUniformLocation(program, "u_Texture0");
	textureUniform1 = glGetUniformLocation(program, "u_Texture1");
	textureUniform2 = glGetUniformLocation(program, "u_Texture2");
	textureUniform3 = glGetUniformLocation(program, "u_Texture3");
	textureUniform4 = glGetUniformLocation(program, "u_Texture4");
	cubeTextureUniform0 = glGetUniformLocation(program, "u_samplerCubeMap0");
	cameraPosUniform = glGetUniformLocation(program, "u_camPos");
	timeUniform = glGetUniformLocation(program, "u_Time");
	lightPosUniform0 = glGetUniformLocation(program, "u_LightPos0");
	lightColorUniform0 = glGetUniformLocation(program, "u_LightColor0");
	lightPosUniform1 = glGetUniformLocation(program, "u_LightPos1");
	lightColorUniform1 = glGetUniformLocation(program, "u_LightColor1");
	lightPosUniform2 = glGetUniformLocation(program, "u_LightPos2");
	lightColorUniform2 = glGetUniformLocation(program, "u_LightColor2");
	stepUniform = glGetUniformLocation(program, "step");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}