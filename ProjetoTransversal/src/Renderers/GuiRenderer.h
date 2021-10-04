#pragma once
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/GuiShader.h"
#include "glm/glm.hpp"

class GuiRenderer
{
public:
	GuiRenderer();
	void RenderGui();

	void CreateProjectionMatrix();
private:
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;
	VertexArray m_vertexArray;
	GuiShader m_shader;
	glm::dmat4 m_projectionMatrix;
};

