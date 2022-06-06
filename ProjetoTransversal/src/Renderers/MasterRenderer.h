#pragma once
#include <glm/glm.hpp>
#include "quadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include "GuiRenderer.h"
#include "WireframeRenderer.h"

class ChunkMesh;
class Player;

class MasterRenderer
{
public:
	MasterRenderer() = default;

	//void DrawQuad(const glm::vec3& position);
	//void DrawCube(const glm::vec3& position);
	//void DrawWireframeCube(const glm::vec3& position);
	void DrawChunk(const ChunkMesh& mesh);
	void finishRender(const Player& player);
private:
	//QuadRenderer m_quadRenderer;
	//CubeRenderer m_cubeRenderer;
	//WireframeRenderer m_wireframeRenderer;
	ChunkRenderer m_chunkRenderer;
	GuiRenderer   m_guiRenderer;
};

