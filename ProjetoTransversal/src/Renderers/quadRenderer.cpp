#include "quadRenderer.h"
#include "Player/Player.h"

QuadRenderer::QuadRenderer()
    :   m_texture("src/res/AtlasTeste.png", 4),
        m_shader("src/shaders/Basic")
{
    m_model.SetData({
    {
        -0.5f, -0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
    },
    {
        0.0f,  0.0f,
        0.0f,  1.0f,
        1.0f,  0.0f,
        1.0f,  1.0f,
    },
    {
        0, 1, 3,
        0, 3, 2,
    } });
}

void QuadRenderer::AddToQueue(const glm::vec3& position)
{
    m_quads.push_back(position);
}

void QuadRenderer::RenderQuads(const Player& player)
{
    m_texture.BindTexture();
    m_model.BindVao();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(player.GetProjectionMatrix());
    m_shader.loadViewMatrix(player.GetViewMatrix());

    for (auto& quad : m_quads)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, quad);

        
        m_shader.loadModelMatrix(model);

        glDrawElements(GL_TRIANGLES, m_model.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
    m_quads.clear();
}