#include "ChunkRenderer.h"
#include "Player/Player.h"
#include "World/Chunk/ChunkMesh.h"

ChunkRenderer::ChunkRenderer()
    :   m_texture("src/res/AtlasTeste.png"),
        m_shader("src/shaders/Basic.glsl")
{
}

void ChunkRenderer::AddToQueue(const ChunkMesh& chunk)
{
    m_chunks.push_back(&chunk);
}

void ChunkRenderer::RenderChunks(const Player player)
{
    static unsigned int numRenders = 0;
    glEnable(GL_CULL_FACE);
    if (m_chunks.empty())
        return;

    m_texture.BindTexture();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(player.GetProjectionMatrix());
    m_shader.loadViewMatrix(player.GetViewMatrix());

    for (const ChunkMesh* chunk : m_chunks)
    {
        numRenders++;
        chunk->GetModel().BindVao();

        glm::mat4 model = glm::mat4(1.0f);

        m_shader.loadModelMatrix(model);
        glDrawElements(GL_TRIANGLES, chunk->GetModel().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
    m_chunks.clear();
}