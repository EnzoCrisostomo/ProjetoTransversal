#include "MasterRenderer.h"
#include "Player/Player.h"
#include <iostream>
#include "OpenGL/ErrorFinder.h"

//void MasterRenderer::DrawWireframeCube(const glm::vec3& position)
//{
//	m_wireframeRenderer.AddToQueue(position);
//}

void MasterRenderer::DrawQuad(const glm::vec2& position, const glm::vec2& dimensions, 
	const float scale, const glm::vec2& textureCoords, const float textureOffset)
{
	m_quadRenderer.AddQuad(position, dimensions, scale, textureCoords, textureOffset);
}

void MasterRenderer::DrawChunk(Chunk* chunk)
{
	m_chunkRenderer.AddToQueue(chunk);
}

void MasterRenderer::renderMenu()
{
	glClearColor(0.40f, 0.80f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_quadRenderer.RenderQuads();

	glCheckError();
}

void MasterRenderer::finishRender(const Player& player)
{
	glClearColor(0.40f, 0.80f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_chunkRenderer.RenderChunks(player);
	//m_guiRenderer.RenderGui();
	//m_wireframeRenderer.RenderWireframe(player);
	glCheckError();
}

void MasterRenderer::UpdateOrthoProjMatrix()
{
	//m_guiRenderer.CreateProjectionMatrix();
	m_quadRenderer.CreateProjectionMatrix();
}