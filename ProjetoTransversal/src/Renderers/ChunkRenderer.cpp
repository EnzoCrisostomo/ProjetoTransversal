#include "ChunkRenderer.h"
#include "Player/Player.h"
#include "World/Chunk/Chunk.h"

ChunkRenderer::ChunkRenderer()
    :   m_texture("src/res/AtlasTeste.png", 4),
        m_vegetationTexture("src/res/AtlasTeste.png", 0),
        m_shader("src/shaders/Basic"),
        m_waterShader("src/shaders/Water.glsl")
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    u_camPos = m_shader.GetUniform("camPos");
    u_chunkPos = m_shader.GetUniform("chunkPos");
}

void ChunkRenderer::AddToQueue(Chunk* chunk)
{
    m_chunks.push_back(chunk);
}

void ChunkRenderer::RenderChunks(const Player& player)
{
    if (m_chunks.empty())
        return;

    RenderBlocks(player);
    RenderVegetation(player);
    RenderWater(player);

    m_chunks.clear();
}

void ChunkRenderer::RenderBlocks(const Player& player)
{
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    m_texture.BindTexture();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(player.GetProjectionMatrix());
    m_shader.loadViewMatrix(player.GetViewMatrix());
    m_shader.LoadVec3(u_camPos, player.GetPosition());

    glm::mat4 model = glm::mat4(1.0f);
    m_shader.loadModelMatrix(model);

    for (Chunk* chunk : m_chunks)
    {
        chunk->GetMesh().GetBlocksModel().BindVao();
        m_shader.LoadVec3(u_chunkPos, glm::vec3(chunk->GetLocation()));

        glDrawElements(GL_TRIANGLES, chunk->GetMesh().GetBlocksModel().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
}

void ChunkRenderer::RenderVegetation(const Player& player)
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    m_vegetationTexture.BindTexture();

    for (Chunk* chunk : m_chunks)
    {
        if (!chunk->GetMesh().HasVegetation())
            continue;
        chunk->GetMesh().GetVegetationModel().BindVao();

        glDrawElements(GL_TRIANGLES, chunk->GetMesh().GetVegetationModel().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
}

void ChunkRenderer::RenderWater(const Player& player)
{
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);

    m_texture.BindTexture();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(player.GetProjectionMatrix());
    m_shader.loadViewMatrix(player.GetViewMatrix());

    glm::mat4 model = glm::mat4(1.0f);
    m_shader.loadModelMatrix(model);

    for (auto it = m_chunks.rbegin(); it != m_chunks.rend(); ++it)
    {
        auto chunk = *it;
        if (!chunk->GetMesh().HasWater())
            continue;
        chunk->GetMesh().GetWaterModel().BindVao();

        glDrawElements(GL_TRIANGLES, chunk->GetMesh().GetWaterModel().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }

    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
}
