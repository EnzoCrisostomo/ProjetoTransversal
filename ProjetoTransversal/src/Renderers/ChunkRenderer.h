#pragma once

#include <vector>

#include "OpenGL/Texture.h"
#include "OpenGL/Shader.h"
class Player;
class Chunk;

class ChunkRenderer
{
public:
	ChunkRenderer();
	void AddToQueue(Chunk* chunk);
	void RenderChunks(const Player& player);

private:
	void RenderBlocks(const Player& player);
	void RenderVegetation(const Player& player);
	void RenderWater(const Player& player);

	GLuint u_camPos;
	GLuint u_chunkPos;
	std::vector<Chunk*> m_chunks;

	Texture m_texture;
	Texture m_vegetationTexture;
	Shader m_shader;
	Shader m_waterShader;
};