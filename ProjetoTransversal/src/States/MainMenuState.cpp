#include "MainMenuState.h"
#include "Renderers/MasterRenderer.h"
#include <iostream>
#include <GLFW/glfw3.h>

MainMenuState::MainMenuState(Application* app)
	: BaseState(app)
{
	glfwSwapInterval(1);
}

MainMenuState::~MainMenuState()
{
}

bool rs;
void MainMenuState::Update(GLFWwindow* window, double elapsedTime)
{
	glfwGetCursorPos(window, &m_mouseX, &m_mouseY);
	m_mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
	//std::cout << "x[" << m_mouseX << "], [" << m_mouseY << "] --> " << m_mousePressed <<"\n";
	rs = (m_mouseX > 400 && m_mouseX < 880) && (m_mouseY > 295 && m_mouseY < 355);

	if(m_mousePressed && rs)
		std::cout << "DISGRAÇA\n";

	std::cout << "Dentro botao --> " << rs <<"\n";
}

void MainMenuState::Render(MasterRenderer* renderer)
{
	renderer->DrawQuad({ 0.f, 35.f }, 60.f + rs * 10.f, 512.f / 64.f);
	renderer->DrawQuad({ 0.f, -35.f }, 60.f, 512.f / 64.f);

	renderer->renderMenu();
}