#pragma once
#include <vector>
#include "OpenGL/Model.h"
#include "OpenGL/Texture.h"
#include "OpenGL/Shader.h"

class Player;

class CubeRenderer
{
public:
	CubeRenderer();
	void AddToQueue(const glm::vec3& position);
	void RenderCubes(const Player& player);

private:
	std::vector<glm::vec3> m_cubes;

	Model m_model;
	Texture m_texture;
	Shader m_shader;
};

