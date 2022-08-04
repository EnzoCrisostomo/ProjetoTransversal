#include "PlayingState.h"
#include "World/World.h"
#include "Application.h"
#include "Player/Player.h"
#include <GLFW/glfw3.h>

namespace PlayingState
{
    static World* m_world;
    static Player m_player;
    static GLFWwindow* m_window;

    void EnterState(GLFWwindow* window, std::string worldName)
    {
        m_window = window;
        m_player = Player(window);
        m_world = new World(m_player, worldName);

        glfwSwapInterval(0);
    }

    void Update(GLFWwindow* window, double elapsedTime)
    {
        const double tickTime = 2.0;
        static double timeCount = 0.0;
        timeCount += elapsedTime;
        m_player.Update(m_world, elapsedTime);

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
    }

    void Render(MasterRenderer* renderer)
    {
        m_world->RenderWorld(renderer, m_player.GetPosition());
        renderer->finishRender(m_player);
    }

    void LeaveState()
    {
        delete m_world;
    }

    void UpdateMatrix()
    {
        m_player.CreateProjectionMatrix();
    }
}