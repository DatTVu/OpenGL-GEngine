#include "stdafx.h"
#include "Object.h"
#include "../Utilities/utilities.h"
#include "ResourceManager.h"
#include <string>

using namespace std;
Object::Object() {
	
}

Object::~Object()
{
}

void Object::Draw(Matrix mvp, float time, Vector3 camPos) {

	glUseProgram(m_objectShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_objectMesh.GetVboId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_objectMesh.GetIboId());

	if (m_objectShader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader->positionAttribute);
		glVertexAttribPointer(m_objectShader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	}
	if (m_objectShader->normalAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader->normalAttribute);
		glVertexAttribPointer(m_objectShader->normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos);
	}
	if (m_objectShader->binormalAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader->binormalAttribute);
		glVertexAttribPointer(m_objectShader->binormalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos + sizenormal);
	}
	if (m_objectShader->tangentAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader->tangentAttribute);
		glVertexAttribPointer(m_objectShader->tangentAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos + sizenormal + sizebinormal);
	}
	if (m_objectShader->textureAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader->textureAttribute);
		glVertexAttribPointer(m_objectShader->textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos + sizenormal + sizebinormal + sizetangent);
	}

	if (m_objectShader->wvpUniform != -1)
	{
		Matrix translationMatrix;

		Matrix scaleMatrix;

		scaleMatrix.SetScale(m_ObjectScale.x, m_ObjectScale.y, m_ObjectScale.z);

		translationMatrix.SetTranslation(m_ObjectPosition.x, m_ObjectPosition.y, m_ObjectPosition.z);

		Matrix worldVPMatrix = translationMatrix* scaleMatrix * mvp;		

		glUniformMatrix4fv(m_objectShader->wvpUniform, 1, GL_FALSE, &worldVPMatrix.m[0][0]);
	}

	if (m_objectShader->worldMatUniform != -1)
	{
		Matrix translationMatrix;

		Matrix scaleMatrix;

		scaleMatrix.SetScale(m_ObjectScale.x, m_ObjectScale.y, m_ObjectScale.z);

		translationMatrix.SetTranslation(m_ObjectPosition.x, m_ObjectPosition.y, m_ObjectPosition.z);

		Matrix worldMatrix = translationMatrix* scaleMatrix;

		glUniformMatrix4fv(m_objectShader->worldMatUniform, 1, GL_FALSE, &worldMatrix.m[0][0]);
	}


	if (m_objectShader->timeUniform != -1) {
		glUniform1f(m_objectShader->timeUniform, time);
	}

	for (int i = 0; i < m_ObjectLightCount; i++) {
		string tempPath = "u_LightPos" + to_string(i);
		unsigned int iLightPosLoc = glGetUniformLocation(m_objectShader->program, &tempPath[0]);
		if (iLightPosLoc != -1) {
			glUniform3f(iLightPosLoc, m_objectLight[i].m_lightPosition.x, m_objectLight[i].m_lightPosition.y, m_objectLight[i].m_lightPosition.z);
		}	
	}

	for (int i = 0; i < m_ObjectLightCount; i++) {
		string tempPath = "u_LightColor" + to_string(i);
		unsigned int iLightColorLoc = glGetUniformLocation(m_objectShader->program, &tempPath[0]);
		if (iLightColorLoc != -1) {
			glUniform3f(iLightColorLoc, m_objectLight[i].m_lightColor.x, m_objectLight[i].m_lightColor.y, m_objectLight[i].m_lightColor.z);
		}	
	}

	for (int i = 0; i < m_ObjectTextCount; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		string tempPath = "u_Texture" + to_string(i);
		glBindTexture(GL_TEXTURE_2D, m_objectText[i].GetTextBufferID());
		int iTextureLoc = glGetUniformLocation(m_objectShader->program, &tempPath[0]);
		if (iTextureLoc != -1)
		{
			glUniform1i(iTextureLoc, 0 + i);
		}
	}
	if (m_objectShader->cameraPosUniform != -1) {
		glUniform4f(m_objectShader->cameraPosUniform, camPos.x, camPos.y, camPos.z, 1.0);
	}
	for (int i = 0; i < m_ObjectCubeTextCount; i++) {
		glActiveTexture(GL_TEXTURE0 + i+ m_ObjectTextCount);
		string tempPath = "u_samplerCubeMap" + to_string(i);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_objectCubeText[i].GetCubeTextID());
		int iTextureLoc = glGetUniformLocation(m_objectShader->program, &tempPath[0]);
		if (iTextureLoc != -1)
		{
			glUniform1i(iTextureLoc, 0 + i+ m_ObjectTextCount);
		}
	}
	glDrawElements(GL_TRIANGLES, m_objectMesh.GetIndicesNum(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	
}

void Object::SetUpMesh(Mesh mesh) {
	m_objectMesh = mesh;	
}

void Object::SetUpTexture(TextureData* texture) {
	m_objectText = new TextureData[m_ObjectTextCount];
	for (int i = 0; i < m_ObjectTextCount; i++)
	{
		m_objectText[i] = texture[m_ObjectTextID[i]];
	}
	
}
void Object::SetUpCubeTexture(CubeTexture* texture) {
	m_objectCubeText = new CubeTexture[m_ObjectCubeTextCount];
	for (int i = 0; i < m_ObjectCubeTextCount; i++)
	{
		m_objectCubeText[i] = texture[m_ObjectCubeTextID[i]];
	}
}

void Object::SetUpShader(Shaders* shader) {
	m_objectShader = &shader[m_ObjectShaderID];	
}

void Object::SetUpLight(LightSource* light) {
	m_objectLight = new LightSource[m_ObjectLightCount];
	for (int i = 0; i < m_ObjectLightCount; i++) {
		m_objectLight[i] = light[m_ObjectLightID[i]];
	}
}
