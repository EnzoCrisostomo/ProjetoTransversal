#include "GuiRenderer.h"
#include <vector>
#include <iostream>
#include "Options/Options.h"

unsigned int shaderProgram;
unsigned int VBO;
GuiRenderer::GuiRenderer()
{
	m_shader.LoadFromFile("src/shaders/Crosshair.glsl");
	m_vertexArray.SetData();
    CreateProjectionMatrix();

    std::vector<float> vertexPositions{
        -1.0f, -10.0f, 0.0f, 
        -1.0f,  10.0f, 0.0f,
         1.0f,  10.0f, 0.0f,
         1.0f, -10.0f, 0.0f, 

        -10.0f, -1.0f, 0.0f,
        -10.0f,  1.0f, 0.0f,
         10.0f,  1.0f, 0.0f,
         10.0f, -1.0f, 0.0f,
    };

    std::vector<unsigned int> indices{
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,
    };

    m_vertexBuffer.SetData(vertexPositions.data(),
		static_cast<unsigned int>(vertexPositions.size()));

	m_indexBuffer.SetData(indices.data(),
		static_cast<unsigned int>(indices.size()));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void GuiRenderer::RenderGui()
{
    glDisable(GL_CULL_FACE);
    m_vertexArray.Bind();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(m_projectionMatrix);
    
    glDrawElements(GL_TRIANGLES, m_indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void GuiRenderer::CreateProjectionMatrix()
{
    /*float aspectRatio = Options::windowWidth / Options::windowHeight;
    if(aspectRatio > 1)
        m_projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -0.0f, 10.f);
    else
        m_projectionMatrix = glm::ortho(-1.0f, 1.0f, -(1 / aspectRatio), 1 / aspectRatio, -0.0f, 10.f);*/

    auto& width = Options::windowWidth;
    auto& height = Options::windowHeight;
    m_projectionMatrix = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, -0.0, 1.0);
}
