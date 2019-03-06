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
	translationUniform = glGetUniformLocation(program, "m4_translation"); //World Matrix Uniform
	textureUniform1 = glGetUniformLocation(program, "u_Texture1");
	textureUniform2 = glGetUniformLocation(program, "u_Texture2");
	textureUniform3 = glGetUniformLocation(program, "u_Texture3");
	textureUniform4 = glGetUniformLocation(program, "u_BlendMap");
	cameraPosUniform = glGetUniformLocation(program, "u_camPos");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}