#include "MasterRenderer.h"
#include "Player.h"
#include <iostream>

//void MasterRenderer::DrawQuad(const glm::vec3& position)
//{
//	m_quadRenderer.AddToQueue(position);
//}

/*void MasterRenderer::DrawCube(const glm::vec3& position)
{
	m_cubeRenderer.AddToQueue(position);
}*/

void MasterRenderer::DrawChunk(const ChunkMesh& mesh)
{
	m_chunkRenderer.AddToQueue(mesh);
}

void MasterRenderer::finishRender(const Player& player)
{
	//m_quadRenderer.RenderQuads(player);
	//m_cubeRenderer.RenderCubes(player);
	m_chunkRenderer.RenderChunks(player);
}
