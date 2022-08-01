#pragma once
#include "OpenGL/Model.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"
#include "glm/glm.hpp"

class QuadRenderer
{
public:
	QuadRenderer();

	void RenderQuads();
	void CreateProjectionMatrix();
private:
	void AddQuad(const glm::vec2& position, const float size = 1.f,
				 const float aspectRatio = 1.f, const glm::vec2 textureCoords = { 0.f, 0.f },
				 const float textureOffset = 1.f);
	Model m_model;
	Mesh m_mesh;
	unsigned int m_indicesCount;

	Shader m_shader;
	Texture m_tempTex;
	glm::dmat4 m_projectionMatrix;
};

