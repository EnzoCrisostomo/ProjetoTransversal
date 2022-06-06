#include "GuiRenderer.h"
#include <vector>
#include <iostream>
#include "Options/Options.h"

unsigned int shaderProgram;
unsigned int VBO;
GuiRenderer::GuiRenderer()
    : m_shader("src/shaders/Gui"), m_tempTex("src/res/Gui.png", 0)
{
    /*Mesh temp;
    temp.vertexPositions = 
    {
        -10.0f, -10.0f, 0.0f,
        -10.0f,  10.0f, 0.0f,
         10.0f,  10.0f, 0.0f,
         10.0f, -10.0f, 0.0f,

        -10.0f, -360.0f, 0.0f,
        -10.0f, -340.0f, 0.0f,
         10.0f, -340.0f, 0.0f,
         10.0f, -360.0f, 0.0f,
    };
    temp.textureCoordinates =
    {
       0.0, 0.0,
       0.0, 1.0,
       1.0, 1.0,
       1.0, 0.0,

       0.0, 0.0,
       0.0, 1.0,
       1.0, 1.0,
       1.0, 0.0,
    };
    temp.indices =
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,
    };*/
    CreateProjectionMatrix();
}



void GuiRenderer::RenderGui()
{
    glEnable(GL_BLEND);
    m_tempTex.BindTexture();
    m_model.BindVao();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(m_projectionMatrix);

    glDrawElements(GL_TRIANGLES, m_model.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

void GuiRenderer::AddQuad(const glm::vec2& position, const float size, const glm::vec2 textureCoords)
{
    m_mesh.vertexPositions.push_back(position.x);
    m_mesh.vertexPositions.push_back(position.y);
    m_mesh.vertexPositions.push_back(0.0f);
    m_mesh.textureCoordinates.push_back(textureCoords.x);
    m_mesh.textureCoordinates.push_back(textureCoords.y);

    m_mesh.vertexPositions.push_back(position.x);
    m_mesh.vertexPositions.push_back(position.y + size);
    m_mesh.vertexPositions.push_back(0.0f);
    m_mesh.textureCoordinates.push_back(textureCoords.x);
    m_mesh.textureCoordinates.push_back(textureCoords.y + 0.5);

    m_mesh.vertexPositions.push_back(position.x + size);
    m_mesh.vertexPositions.push_back(position.y + size);
    m_mesh.vertexPositions.push_back(0.0f);
    m_mesh.textureCoordinates.push_back(textureCoords.x + 0.5);
    m_mesh.textureCoordinates.push_back(textureCoords.y + 0.5);

    m_mesh.vertexPositions.push_back(position.x + size);
    m_mesh.vertexPositions.push_back(position.y);
    m_mesh.vertexPositions.push_back(0.0f);
    m_mesh.textureCoordinates.push_back(textureCoords.x + 0.5);
    m_mesh.textureCoordinates.push_back(textureCoords.y);

    m_mesh.indices.insert(m_mesh.indices.end(),
        {
            m_indicesCount,
            m_indicesCount + 1,
            m_indicesCount + 2,

            m_indicesCount + 2,
            m_indicesCount + 3,
            m_indicesCount
        });
    m_indicesCount += 4;
}

void GuiRenderer::CreateProjectionMatrix()
{
    auto& width = Options::windowWidth;
    auto& height = Options::windowHeight;
    //m_projectionMatrix = glm::ortho(0.0, width, 0.0, height, -0.0, 1.0);
    BuildGui();
    m_projectionMatrix = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, -0.0, 1.0);
}

void GuiRenderer::BuildGui()
{
    AddQuad({ -10, -10 }, 20, { 0, 0 });
    for (int i  = 0; i < 8; i++)
        AddQuad({ 50.0 * i -200.0, -Options::windowHeight/2 + 5}, 50, { 0, 0.5 });
    m_model.SetData(m_mesh);
    m_mesh.Free();
    m_indicesCount = 0;
}
