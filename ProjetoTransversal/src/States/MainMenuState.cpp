#include "MainMenuState.h"
#include "Renderers/MasterRenderer.h"
#include <iostream>
#include <GLFW/glfw3.h>

MainMenuState::MainMenuState(Application* app)
	: BaseState(app)
{
	glfwSwapInterval(1);

	m_buttons.emplace_back(glm::vec2{ 0.f, 35.f }, glm::vec2{ 512.f, 64.f });
	m_buttons.emplace_back(glm::vec2{ 0.f, -35.f }, glm::vec2{ 512.f, 64.f });
}

MainMenuState::~MainMenuState()
{
}

bool rs;
void MainMenuState::Update(GLFWwindow* window, double elapsedTime)
{
	glfwGetCursorPos(window, &m_mouseX, &m_mouseY);
	m_mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
	std::cout << "x[" << m_mouseX << "], [" << m_mouseY << "] --> " << m_mousePressed <<"\n";

	if(m_mousePressed)
		for (auto& button : m_buttons)
		{
			if (button.IsHovered(m_mouseX, m_mouseY))
			{
				std::cout << "DISGRAÇA";
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
}

void MainMenuState::Config()
{
}

void MainMenuState::Sair()
{
}
