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

};