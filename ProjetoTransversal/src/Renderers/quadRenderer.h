#pragma once

#include <vector>

#include "OpenGL/Model.h"
#include "OpenGL/Texture.h"
#include "OpenGL/Shader.h"
class Player;

class QuadRenderer
{
public:
	QuadRenderer();
	void AddToQueue(const glm::vec3& position);
	void RenderQuads(const Player& player);

private:
	std::vector<glm::vec3> m_quads;

	Model m_model;
	Texture m_texture;
	Shader m_shader;
};