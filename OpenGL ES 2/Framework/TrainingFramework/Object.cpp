#include "stdafx.h"
#include "Object.h"
#include "../Utilities/utilities.h"
#include "ResourceManager.h"

Object::Object() {
}

Object::~Object()
{
}

void Object::Draw(Matrix mvp) {	
	
	glUseProgram(m_objectShader.program);
	glBindBuffer(GL_ARRAY_BUFFER, m_objectMesh.GetVboId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_objectMesh.GetIboId());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_objectText.GetTextBufferID());

	int iTextureLoc = glGetUniformLocation(m_objectShader.program, "u_Texture1");
	glUniform1i(iTextureLoc, 0);

	if (m_objectShader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader.positionAttribute);
		glVertexAttribPointer(m_objectShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	}
	if (m_objectShader.normalAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader.normalAttribute);
		glVertexAttribPointer(m_objectShader.normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos);
	}
	if (m_objectShader.binormalAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader.binormalAttribute);
		glVertexAttribPointer(m_objectShader.binormalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos + sizenormal);
	}
	if (m_objectShader.tangentAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader.tangentAttribute);
		glVertexAttribPointer(m_objectShader.tangentAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos + sizenormal + sizebinormal);
	}
	if (m_objectShader.textureAttribute != -1)
	{
		glEnableVertexAttribArray(m_objectShader.textureAttribute);
		glVertexAttribPointer(m_objectShader.textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizepos + sizenormal + sizebinormal + sizetangent);
	}

	if (m_objectShader.translationUniform != -1)
	{
		Matrix translationMatrix;

		translationMatrix.SetTranslation(m_ObjectPosition.x, m_ObjectPosition.y, m_ObjectPosition.z);

		mvp = translationMatrix * mvp;

		glUniformMatrix4fv(m_objectShader.translationUniform, 1, GL_FALSE, &mvp.m[0][0]);
	}

	glDrawElements(GL_TRIANGLES, m_objectMesh.GetIndicesNum(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, 0);	
	
}

void Object::SetUpMesh(Mesh mesh) {
	m_objectMesh = mesh;	
}

void Object::SetUpTexture(TextureData texture) {
	m_objectText = texture;
}

void Object::SetUpShader(Shaders* shader) {
	m_objectShader = shader[m_ObjectShaderID];	
}
