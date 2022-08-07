#include "States.h"
#include "Renderers/MasterRenderer.h"
#include "Application.h"
#include <iostream>
#include <GLFW/glfw3.h>

MainMenuState::MainMenuState(Application* app, GLFWwindow* window)
	: BaseState(app, window)
{
	glfwSwapInterval(1);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	m_buttons.emplace_back(glm::vec2{ 0.f, 35.f }, glm::vec2{ 512.f, 64.f }, this, &MainMenuState::Jogar);
	m_buttons.emplace_back(glm::vec2{ 0.f, -35.f }, glm::vec2{ 512.f, 64.f }, this, &MainMenuState::Config);
	m_buttons.emplace_back(glm::vec2{ 0.f, -105.f }, glm::vec2{ 512.f, 64.f }, this, &MainMenuState::Sair);
}

MainMenuState::~MainMenuState()
{
}

bool rs;
void MainMenuState::Update(double elapsedTime)
{
	glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);
	m_mousePressed = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;

	for (auto& button : m_buttons)
	{
		button.Update(m_mouseX, m_mouseY, m_mousePressed);
	}
}

void MainMenuState::Render(MasterRenderer* renderer)
{
	for (auto& button : m_buttons)
	{
		renderer->DrawQuad(button.GetPosition(), button.GetDimensions());
	}
	//renderer->DrawQuad({ 0.f, 35.f }, 60.f, 512.f / 64.f);
	//renderer->DrawQuad({ 0.f, -35.f }, 60.f, 512.f / 64.f);

	renderer->renderMenu();
}


void MainMenuState::Jogar()
{
	std::cout << "Jogar!\n";

	PlayingState* newState = new PlayingState(m_application, m_window, "teste");

	m_application->ChangeState(static_cast<BaseState*>(newState));
}

void MainMenuState::Config()
{
	std::cout << "Config!\n";
}

void MainMenuState::Sair()
{
	std::cout << "Sair!\n";
	m_application->ChangeState(nullptr);
}
