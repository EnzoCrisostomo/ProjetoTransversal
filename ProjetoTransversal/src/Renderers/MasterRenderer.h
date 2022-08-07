#pragma once
#include <glm/glm.hpp>
#include "ChunkRenderer.h"
//#include "GuiRenderer.h"
#include "QuadRenderer.h"
//#include "WireframeRenderer.h"

class Chunk;
class Player;

class MasterRenderer
{
public:
	MasterRenderer() = default;

	//void DrawWireframeCube(const glm::vec3& position);
	void DrawQuad(const glm::vec2& position, const glm::vec2& dimensions,
		const float scale = 1.f, const glm::vec2& textureCoords = { 0.f, 0.f },
		const float textureOffset = 1.f);
	void DrawChunk(Chunk* chunk);
	void renderMenu();
	void finishRender(const Player& player);

private:
	//WireframeRenderer m_wireframeRenderer;
	ChunkRenderer m_chunkRenderer;
	QuadRenderer m_quadRenderer;
	//GuiRenderer   m_guiRenderer;
};

