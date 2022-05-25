#include "ChunkRenderer.h"
#include "Player/Player.h"
#include "World/Chunk/ChunkMesh.h"

ChunkRenderer::ChunkRenderer()
    :   m_texture("src/res/AtlasTeste.png", 4),
        m_vegetationTexture("src/res/AtlasTeste.png", 0),
        m_shader("src/shaders/Basic.glsl")
{
}

void ChunkRenderer::AddToQueue(const ChunkMesh& chunk)
{
    m_chunks.push_back(&chunk);
}

void ChunkRenderer::RenderChunks(const Player& player)
{
    if (m_chunks.empty())
        return;

    RenderBlocks(player);
    RenderVegetation(player);
    //RenderWater(player);

    m_chunks.clear();
}

void ChunkRenderer::RenderBlocks(const Player& player)
{
    glEnable(GL_CULL_FACE);
    m_texture.BindTexture();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(player.GetProjectionMatrix());
    m_shader.loadViewMatrix(player.GetViewMatrix());

    glm::mat4 model = glm::mat4(1.0f);
    m_shader.loadModelMatrix(model);

    for (const ChunkMesh* chunk : m_chunks)
    {
        chunk->GetBlocksModel().BindVao();

        glDrawElements(GL_TRIANGLES, chunk->GetBlocksModel().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
}

void ChunkRenderer::RenderVegetation(const Player& player)
{
    glDisable(GL_CULL_FACE);
    m_vegetationTexture.BindTexture();

    for (const ChunkMesh* chunk : m_chunks)
    {
        chunk->GetVegetationModel().BindVao();

        glDrawElements(GL_TRIANGLES, chunk->GetVegetationModel().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
}

void ChunkRenderer::RenderWater(const Player& player)
{
}
