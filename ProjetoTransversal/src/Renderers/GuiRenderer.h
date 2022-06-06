#pragma once
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"
#include "glm/glm.hpp"

class GuiRenderer
{
public:
	GuiRenderer();

	void RenderGui();

private:
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;
	VertexArray m_vertexArray;

	Shader m_shader;
};

