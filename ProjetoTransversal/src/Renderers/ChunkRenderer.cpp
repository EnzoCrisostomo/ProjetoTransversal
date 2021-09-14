#include "ChunkRenderer.h"
#include "Player.h"
#include "World/ChunkMesh.h"

ChunkRenderer::ChunkRenderer()
{
    //TODO inicializaton list
    m_texture.loadFromFile("src/res/Atlas.png");
    m_shader.LoadFromFile("src/shaders/Basic.glsl");
}

void ChunkRenderer::AddToQueue(const ChunkMesh& chunk)
{
    m_chunks.push_back(&chunk);
}

void ChunkRenderer::RenderChunks(const Player& player)
{
    if (m_chunks.empty())
        return;

    glEnable(GL_CULL_FACE);
    m_texture.BindTexture();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(player.GetProjectionMatrix());
    m_shader.loadViewMatrix(player.GetViewMatrix());

    for (const ChunkMesh* chunk : m_chunks)
    {
        chunk->GetModel().BindVao();

        glm::mat4 model = glm::mat4(1.0f);

        m_shader.loadModelMatrix(model);
        glDrawElements(GL_TRIANGLES, chunk->GetModel().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
    m_chunks.clear();
}