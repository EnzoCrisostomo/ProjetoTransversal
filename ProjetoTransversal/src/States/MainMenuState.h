#pragma once
#include "BaseState.h"

class MainMenuState : public BaseState
{
public:
	MainMenuState(Application* app);
	~MainMenuState();

	void Update(GLFWwindow* window, double elapsedTime) override;
	void Render(MasterRenderer* renderer) override;

private:
	bool m_mousePressed = false;
	double m_mouseX = 0, m_mouseY = 0;
};