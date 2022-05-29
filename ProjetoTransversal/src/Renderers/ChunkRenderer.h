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

	void RenderBlocks(const Player& player);
	void RenderVegetation(const Player& player);
	void RenderWater(const Player& player);

	std::vector<const ChunkMesh*> m_chunks;

	Texture m_texture;
	Texture m_vegetationTexture;
	Shader m_shader;
	Shader m_waterShader;
};