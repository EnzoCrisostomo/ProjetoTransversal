#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "quadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"

class ChunkMesh;
class Player;

class MasterRenderer
{
public:
	MasterRenderer() = default;

	//void DrawQuad(const glm::vec3& position);
	//void DrawCube(const glm::vec3& position);
	void DrawChunk(const ChunkMesh& mesh);
	void finishRender(const Player& player);
private:
	//QuadRenderer m_quadRenderer;
	//CubeRenderer m_cubeRenderer;
	ChunkRenderer m_chunkRenderer;
};

