#include "QuadRenderer.h"

#include <vector>
#include <iostream>
#include "Options/Options.h"

static const size_t maxQuadCount = 100;
static const size_t maxVertexCount = maxQuadCount * 4;
static const size_t maxIndexCount = maxQuadCount * 6;

QuadRenderer::QuadRenderer()
    : m_shader("src/shaders/Gui"), m_tempTex("src/res/Menu/Jogar.png", 0)
{
    CreateProjectionMatrix();


    m_vertexArray.SetData();
    m_vertexBuffer.SetData<Vertex>(nullptr , maxVertexCount);

    //Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, positions));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoords));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);

    unsigned int indices[maxIndexCount];
    unsigned int offset = 0;

    for (int i = 0; i < maxIndexCount; i += 6)
    {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }
    m_indexBuffer.SetData(indices, maxIndexCount);
}

void QuadRenderer::RenderQuads()
{
    m_vertexBuffer.Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_vertexData.size(), m_vertexData.data());

    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    m_tempTex.BindTexture();
    m_vertexArray.Bind();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(m_projectionMatrix);

    glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, nullptr);

    m_vertexData.clear();
    m_indicesCount = 0;
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
        {1.f, 1.f, 1.f, 1.f}
    };
    m_vertexData.push_back(vertice);

    vertice = {
        {position.x - numX, position.y + numY, 0.f},
        {textureCoords.x, textureCoords.y + textureOffset},
        {1.f, 1.f, 1.f, 1.f}
    };
    m_vertexData.push_back(vertice);

    vertice = {
        {position.x + numX, position.y + numY, 0.f},
        {textureCoords.x + textureOffset, textureCoords.y + textureOffset},
        {1.f, 1.f, 1.f, 1.f}
    };
    m_vertexData.push_back(vertice);

    vertice = {
        {position.x + numX, position.y - numY, 0.f},
        {textureCoords.x + textureOffset, textureCoords.y},
        {1.f, 1.f, 1.f, 1.f}
    };
    m_vertexData.push_back(vertice);

    m_indicesCount += 6;
}

void QuadRenderer::CreateProjectionMatrix()
{
    auto& width = Options::windowWidth;
    auto& height = Options::windowHeight;
    //m_projectionMatrix = glm::ortho(0.0, width, 0.0, height, -0.0, 1.0);
    m_projectionMatrix = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, -0.0, 1.0);
}