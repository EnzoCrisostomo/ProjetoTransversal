#pragma once

struct GLFWwindow;
class MasterRenderer;

namespace MainMenuState
{
	void EnterState();
	void Update(GLFWwindow* window, double elapsedTime);
	void Render(MasterRenderer* renderer);
	void LeaveState();

	//Button functions

	void Jogar();
	void Config();
	void Sair();
};