#include "stdafx.h"
#include "EffectsManager.h"
#include "Vertex.h"
#include <iostream>

#include "Globals.h"

using namespace std;


EffectsManager * EffectsManager::ms_pInstance = NULL;

void EffectsManager::CreateQuad() {

	Vertex quadVertices[4];
	quadVertices[0].pos.x = 1.0f;  quadVertices[0].pos.y = 1.0f;  quadVertices[0].pos.z = 0.0f;
	quadVertices[1].pos.x = 1.0f;  quadVertices[1].pos.y = -1.0f;  quadVertices[1].pos.z = 0.0f;
	quadVertices[2].pos.x = -1.0f;  quadVertices[2].pos.y = -1.0f;  quadVertices[2].pos.z = 0.0f;
	quadVertices[3].pos.x = -1.0f;	quadVertices[3].pos.y = 1.0f;	quadVertices[3].pos.z = 0.0f;
	quadVertices[0].uv.x = 1.0f;  quadVertices[0].uv.y = 1.0f;
	quadVertices[1].uv.x = 1.0f;  quadVertices[1].uv.y = 0.0f;
	quadVertices[2].uv.x = 0.0f;  quadVertices[2].uv.y = 0.0f;
	quadVertices[3].uv.x = 0.0f;  quadVertices[3].uv.y = 1.0f;
	//index data
	unsigned int idx[] = { 0, 1, 2, 0, 2, 3 };
	glGenBuffers(1, &m_quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_quadIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quadIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EffectsManager::LoadData(const char* effectManagerPath) {
	FILE* effectFile;
	if (fopen_s(&effectFile, effectManagerPath, "r") != 0)
	{
		cout << " Failed to open Effect Manager Data file" << endl;
		return;
	}
	////////////////////////
	char limit[50];
	int count;

	fgets(limit, sizeof(limit), effectFile);
	sscanf_s(limit, "#Shaders: %d", &count);
	m_effectShaders = new Shaders[count]; 
	int i = 0;
	while (!feof(effectFile) && i < count) {
		char fakepath[100];
		char vspath[100] = "../Resources/";
		char fakepath2[100];
		char fspath[100] = "../Resources/";

		fgets(limit, sizeof(limit), effectFile);
		sscanf_s(limit, "ID %d", &m_effectShaders[i].m_EmShaderID);

		fgets(limit, sizeof(limit), effectFile);
		sscanf(limit, "VS %s", &fakepath, 100);
		strcat(vspath, fakepath);
		cout << vspath << endl;

		fgets(limit, sizeof(limit), effectFile);
		sscanf(limit, "FS %s", &fakepath2, 100);
		strcat(fspath, fakepath2);
		cout << fspath << endl;
		m_effectShaders[i].Init(vspath, fspath);

		strcpy(m_effectShaders[i].fileVS, vspath);
		strcpy(m_effectShaders[i].fileFS, fspath);
		i++;
	}
	i = 0;
	fseek(effectFile, 2, SEEK_CUR);

	fgets(limit, sizeof(limit), effectFile);
	sscanf_s(limit, "#FBO: %d", &count);
	if (count <= 0) {return;} //make sure we have a valid number of effects!
	m_framebufferID = new GLuint[count];
	glGenFramebuffers(count, m_framebufferID); 
	m_colorTexID =  new GLuint[count];
	m_depthTexID = new GLuint[count];
	for (int j = 0; j < count; j++) {
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID[j]);

		glGenTextures(1, &m_colorTexID[j]);
		glBindTexture(GL_TEXTURE_2D, m_colorTexID[j]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Globals::screenWidth, Globals::screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTexID[j], 0);

		glGenTextures(1, &m_depthTexID[j]);
		glBindTexture(GL_TEXTURE_2D, m_depthTexID[j]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Globals::screenWidth, Globals::screenHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexID[j], 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {}
		else { cout << "Frame Buffer is not finished" << endl; }
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	i = 0;
	fseek(effectFile, 2, SEEK_CUR);

	fgets(limit, sizeof(limit), effectFile);
	sscanf_s(limit, "#Effects: %d", &count);
	m_EmEffect = new Effects[count];
	while (!feof(effectFile) && i < count) {
		fgets(limit, sizeof(limit), effectFile);
		sscanf_s(limit, "#ID %d", &m_EmEffect[i].m_effectID);
		fgets(limit, sizeof(limit), effectFile); //Skip effect name
		fgets(limit, sizeof(limit), effectFile);
		sscanf_s(limit, "#NoPasses: %d", &m_EmEffect[i].m_effectPassCount);
		m_EmEffect[i].m_effectPass = new Pass[m_EmEffect[i].m_effectPassCount];
		for (int k = 0; k < m_EmEffect[i].m_effectPassCount; k++) {
			fgets(limit, sizeof(limit), effectFile);
			sscanf_s(limit, "#PassID %d", &m_EmEffect[i].m_effectPass[k].m_passID);
			fgets(limit, sizeof(limit), effectFile); //Skip pass name
			fgets(limit, sizeof(limit), effectFile);
			sscanf_s(limit, "#ShaderID %d", &m_EmEffect[i].m_effectPass[k].m_passShaderID);
			fgets(limit, sizeof(limit), effectFile);
			sscanf_s(limit, "#ColorTextureCount: %d", &m_EmEffect[i].m_effectPass[k].m_passColorTextureCount);
			m_EmEffect[i].m_effectPass[k].m_passColorTextureID = new int[m_EmEffect[i].m_effectPass[k].m_passColorTextureCount];
			for (int l = 0; l < m_EmEffect[i].m_effectPass[k].m_passColorTextureCount; l++) {
				fgets(limit, sizeof(limit), effectFile);
				sscanf_s(limit, "#ColorTexture: %d", &m_EmEffect[i].m_effectPass[k].m_passColorTextureID[l]);
			}
			fgets(limit, sizeof(limit), effectFile);
			sscanf_s(limit, "#DepthTextureCount: %d", &m_EmEffect[i].m_effectPass[k].m_passDepthTextureCount);
			m_EmEffect[i].m_effectPass[k].m_passDepthTextureID = new int[m_EmEffect[i].m_effectPass[k].m_passDepthTextureCount];
			for (int l = 0; l < m_EmEffect[i].m_effectPass[k].m_passDepthTextureCount; l++) {
				fgets(limit, sizeof(limit), effectFile);
				sscanf_s(limit, "DepthTexture: %d", &m_EmEffect[i].m_effectPass[k].m_passDepthTextureID[l]);
			}
			
		}
	}
	i = 0;
	fclose(effectFile);
}