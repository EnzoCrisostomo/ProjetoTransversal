#include "MainMenuState.h"
#include "Renderers/MasterRenderer.h"
#include <iostream>
#include <GLFW/glfw3.h>

MainMenuState::MainMenuState(Application* app)
	: BaseState(app)
{
	glfwSwapInterval(1);

	m_buttons.emplace_back(glm::vec2{ 0.f, 35.f }, glm::vec2{ 512.f, 64.f }, &MainMenuState::Jogar);
	m_buttons.emplace_back(glm::vec2{ 0.f, -35.f }, glm::vec2{ 512.f, 64.f }, &MainMenuState::Config);
	m_buttons.emplace_back(glm::vec2{ 0.f, -105.f }, glm::vec2{ 512.f, 64.f }, &MainMenuState::Sair);
}

MainMenuState::~MainMenuState()
{
}

bool rs;
void MainMenuState::Update(GLFWwindow* window, double elapsedTime)
{
	glfwGetCursorPos(window, &m_mouseX, &m_mouseY);
	m_mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;

	if(m_mousePressed)
		for (auto& button : m_buttons)
		{
			if (button.IsHovered(m_mouseX, m_mouseY))
			{
				(this->*button.m_function)();
			}
		}
}

void MainMenuState::Render(MasterRenderer* renderer)
{
	for (auto& button : m_buttons)
	{
		renderer->DrawQuad(button.m_position, button.m_dimensions);
	}
	//renderer->DrawQuad({ 0.f, 35.f }, 60.f, 512.f / 64.f);
	//renderer->DrawQuad({ 0.f, -35.f }, 60.f, 512.f / 64.f);

	renderer->renderMenu();
}

void MainMenuState::Jogar()
{
	std::cout << "Jogar!\n";
}

void MainMenuState::Config()
{
	std::cout << "Config!\n";
}

void MainMenuState::Sair()
{
	std::cout << "Sair!\n";
}
