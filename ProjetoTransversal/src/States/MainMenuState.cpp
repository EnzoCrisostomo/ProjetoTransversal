#include "MainMenuState.h"
#include "Renderers/MasterRenderer.h"
#include <iostream>
#include <GLFW/glfw3.h>

MainMenuState::MainMenuState(Application* app)
	: BaseState(app)
{

}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Update(GLFWwindow* window, double elapsedTime)
{
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	//std::cout << "x[" << xPos << "], [" << yPos << "]\n";
}

void MainMenuState::Render(MasterRenderer* renderer)
{
	renderer->renderMenu();
}