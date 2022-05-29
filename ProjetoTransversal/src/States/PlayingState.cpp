#include "PlayingState.h"
#include "World/World.h"
#include "Application.h"

PlayingState::PlayingState(Application* app, GLFWwindow* window, std::string worldName)
	: BaseState(app), m_window(window), m_player(window, this)
{
    m_world = new World(m_player, worldName);
}

PlayingState::~PlayingState()
{
    delete m_world;
}

void PlayingState::Update(double elapsedTime)
{
    m_player.Update(m_world, elapsedTime);

    m_world->UpdateWorld(m_player);
}

void PlayingState::UpdateMatrix()
{
    m_player.CreateProjectionMatrix();
}

void PlayingState::Render(MasterRenderer* renderer)
{
    m_world->RenderWorld(renderer, m_player.GetPosition());
    renderer->finishRender(m_player);
}

void PlayingState::LeaveState()
{
    m_application->ChangeState(State::Menu);
}
