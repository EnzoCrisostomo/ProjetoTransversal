#pragma once
#include "BaseState.h"

class MainMenuState : BaseState
{
public:
	MainMenuState(Application* app);

	void Update(double elapsedTime) override;
	void Render(MasterRenderer* renderer) override;
};