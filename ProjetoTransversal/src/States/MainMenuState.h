#pragma once
#include "BaseState.h"
#include "MenuButton.h"
#include <vector>

class MainMenuState : public BaseState
{
public:
	MainMenuState(Application* app);
	~MainMenuState();

	void Update(GLFWwindow* window, double elapsedTime) override;
	void Render(MasterRenderer* renderer) override;

private:
	std::vector<MenuButton<MainMenuState>> m_buttons;

	bool m_mousePressed = false;
	double m_mouseX = 0, m_mouseY = 0;

	//Button functions

	void Jogar();
	void Config();
	void Sair();
};