#include "MasterRenderer.h"
#include "Player/Player.h"
#include <iostream>
#include "OpenGL/ErrorFinder.h"

//void MasterRenderer::DrawQuad(const glm::vec3& position)
//{
//	m_quadRenderer.AddToQueue(position);
//}

//void MasterRenderer::DrawCube(const glm::vec3& position)
//{
//	m_cubeRenderer.AddToQueue(position);
//}

//void MasterRenderer::DrawWireframeCube(const glm::vec3& position)
//{
//	m_wireframeRenderer.AddToQueue(position);
//}

void MasterRenderer::DrawChunk(const ChunkMesh& mesh)
{
	m_chunkRenderer.AddToQueue(mesh);
}

void MasterRenderer::finishRender(const Player& player)
{
	glClearColor(0.40f, 0.80f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//m_quadRenderer.RenderQuads(player);
	m_chunkRenderer.RenderChunks(player);
	m_guiRenderer.RenderGui();
	//m_cubeRenderer.RenderCubes(player);
	//m_wireframeRenderer.RenderWireframe(player);
	//glCheckError();
}
