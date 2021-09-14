#pragma once

#include <vector>

#include "OpenGL/Texture.h"
#include "OpenGL/Shader.h"
class Player;
class ChunkMesh;

class ChunkRenderer
{
public:
	ChunkRenderer();
	void AddToQueue(const ChunkMesh& chunk);
	void RenderChunks(const Player& player);

private:
	std::vector<const ChunkMesh*> m_chunks;

	Texture m_texture;
	Shader m_shader;
};