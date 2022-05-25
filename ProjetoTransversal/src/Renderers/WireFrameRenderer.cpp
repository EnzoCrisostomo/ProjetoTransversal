#include "WireFrameRenderer.h"
#include "Player/Player.h"

WireframeRenderer::WireframeRenderer()
    :   m_texture("src/res/AtlasTeste.png", 4),
        m_shader("src/shaders/Basic.glsl")
{
    m_model.SetData({
    {
            //Front
            0, 0, 0,
            0, 1, 0,
            1, 1, 0,
            1, 0, 0,

            //Back
            1, 0, 1,
            1, 1, 1,
            0, 1, 1,
            0, 0, 1,

            //Right
            1, 0, 0,
            1, 1, 0,
            1, 1, 1,
            1, 0, 1,

            //Left
            0, 0, 1,
            0, 1, 1,
            0, 1, 0,
            0, 0, 0,

            //Top
            0, 1, 1,
            1, 1, 1,
            1, 1, 0,
            0, 1, 0,

            //Bottom
            0, 0, 1,
            0, 0, 0,
            1, 0, 0,
            1, 0, 1,
    },
    {
        0.00f,  0.50f,
        0.00f,  0.75f,
        0.25f,  0.75f,
        0.25f,  0.50f,

        0.00f,  0.50f,
        0.00f,  0.75f,
        0.25f,  0.75f,
        0.25f,  0.50f,

        0.00f,  0.50f,
        0.00f,  0.75f,
        0.25f,  0.75f,
        0.25f,  0.50f,

        0.00f,  0.50f,
        0.00f,  0.75f,
        0.25f,  0.75f,
        0.25f,  0.50f,

        0.00f,  0.50f,
        0.00f,  0.75f,
        0.25f,  0.75f,
        0.25f,  0.50f,

        0.00f,  0.50f,
        0.00f,  0.75f,
        0.25f,  0.75f,
        0.25f,  0.50f,
    },
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    } });
}

void WireframeRenderer::AddToQueue(const glm::vec3& position)
{
    m_cubes.push_back(position);
}

void WireframeRenderer::RenderWireframe(const Player& player)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_texture.BindTexture();
    m_model.BindVao();
    m_shader.Bind();
    m_shader.loadProjectionMatrix(player.GetProjectionMatrix());
    m_shader.loadViewMatrix(player.GetViewMatrix());

    for (auto& cube : m_cubes)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cube);

        m_shader.loadModelMatrix(model);

        glDrawElements(GL_TRIANGLES, m_model.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
    m_cubes.clear();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}