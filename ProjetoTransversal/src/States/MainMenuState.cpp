#include "MainMenuState.h"
#include "Renderers/MasterRenderer.h"
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include "MenuButton.h"


namespace MainMenuState
{
	static std::vector<MenuButton> m_buttons;
	static bool m_mousePressed = false;
	static double m_mouseX = 0, m_mouseY = 0;

	void EnterState()
	{
		glfwSwapInterval(1);

		m_buttons.emplace_back(glm::vec2{ 0.f, 35.f }, glm::vec2{ 512.f, 64.f }, Jogar);
		m_buttons.emplace_back(glm::vec2{ 0.f, -35.f }, glm::vec2{ 512.f, 64.f }, Config);
		m_buttons.emplace_back(glm::vec2{ 0.f, -105.f }, glm::vec2{ 512.f, 64.f }, Sair);
	}

	void Update(GLFWwindow* window, double elapsedTime)
	{
		glfwGetCursorPos(window, &m_mouseX, &m_mouseY);
		m_mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;

		if(m_mousePressed)
			for (auto& button : m_buttons)
			{
				if (button.IsHovered(m_mouseX, m_mouseY))
				{
					(button.m_function)();
				}
			}
	}

	void Render(MasterRenderer* renderer)
	{
		for (auto& button : m_buttons)
		{
			renderer->DrawQuad(button.m_position, button.m_dimensions);
		}
		//renderer->DrawQuad({ 0.f, 35.f }, 60.f, 512.f / 64.f);
		//renderer->DrawQuad({ 0.f, -35.f }, 60.f, 512.f / 64.f);

		renderer->renderMenu();
	}

	void LeaveState()
	{

	}

	void Jogar()
	{
		std::cout << "Jogar!\n";
	}

	void Config()
	{
		std::cout << "Config!\n";
	}

	void Sair()
	{
		std::cout << "Sair!\n";
	}
}
