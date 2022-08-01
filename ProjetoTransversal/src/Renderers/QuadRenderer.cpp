#include "QuadRenderer.h"

#include <vector>
#include <iostream>
#include "Options/Options.h"

QuadRenderer::QuadRenderer()
    : m_shader("src/shaders/Gui"), m_tempTex("src/res/Menu/Jogar.png", 0)
{
    CreateProjectionMatrix();
    AddQuad({ 0.f, 55.f }, 100.f, 512.f/64.f);
    AddQuad({ 0.f, -55.f }, 100.f, 512.f/64.f);
    m_model.SetData(m_mesh);
}

void QuadRenderer::RenderQuads()
{
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    m_tempTex.BindTexture();
    m_model.BindVao();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(m_projectionMatrix);

    glDrawElements(GL_TRIANGLES, m_model.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

void QuadRenderer::AddQuad( const glm::vec2& position, const float size,
                            const float aspectRatio, const glm::vec2 textureCoords,
                            const float textureOffset)
{
    float numX = size * aspectRatio / 2.f;
    float numY = size / 2.f;
    Vertex vertice = { 
        {position.x - numX, position.y - numY, 0.f},
        {textureCoords.x, textureCoords.y},
        {1.f, 1.f, 1.f}
    };
    m_mesh.vertices.push_back(vertice);

    vertice = {
        {position.x - numX, position.y + numY, 0.f},
        {textureCoords.x, textureCoords.y + textureOffset},
        {1.f, 1.f, 1.f}
    };
    m_mesh.vertices.push_back(vertice);

    vertice = {
        {position.x + numX, position.y + numY, 0.f},
        {textureCoords.x + textureOffset, textureCoords.y + textureOffset},
        {1.f, 1.f, 1.f}
    };
    m_mesh.vertices.push_back(vertice);

    vertice = {
        {position.x + numX, position.y - numY, 0.f},
        {textureCoords.x + textureOffset, textureCoords.y},
        {1.f, 1.f, 1.f}
    };
    m_mesh.vertices.push_back(vertice);

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

void QuadRenderer::CreateProjectionMatrix()
{
    auto& width = Options::windowWidth;
    auto& height = Options::windowHeight;
    //m_projectionMatrix = glm::ortho(0.0, width, 0.0, height, -0.0, 1.0);
    m_projectionMatrix = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, -0.0, 1.0);
}