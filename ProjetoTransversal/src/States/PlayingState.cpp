#include "States.h"
#include "World/World.h"
#include "Application.h"

PlayingState::PlayingState(Application* app, GLFWwindow* window, std::string worldName)
	: BaseState(app, window), m_player()
{
    glfwSwapInterval(0);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_world = new World(m_player, worldName);
}

PlayingState::~PlayingState()
{
    delete m_world;
}

void PlayingState::Update(double elapsedTime)
{
    const double tickTime = 2.0;
    static double timeCount = 0.0;
    timeCount += elapsedTime;

    m_player.Update(m_world, m_window, elapsedTime);

    m_world->UpdateWorld(m_player);
    if (timeCount > tickTime)
    {
        timeCount -= tickTime;
        /*static BlockId block = BlockId::Grass;
        glm::ivec3 blockPos = m_player.GetPosition();
        blockPos.x += 3;
        blockPos.z += 3;
        m_world->SetBlock(blockPos, block);
        int value = (int)block+1;
        if (value >= (int)BlockId::blockCount)
            value = 0;
        block = (BlockId)value;*/
    }

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        m_application->ChangeState(new MainMenuState(m_application, m_window));
}

void PlayingState::Render(MasterRenderer* renderer)
{
    m_player.CreateProjectionMatrix();
    m_world->RenderWorld(renderer, m_player.GetPosition());
    renderer->finishRender(m_player);
}

void PlayingState::LeaveState()
{
    m_application->ChangeState(nullptr);
}
