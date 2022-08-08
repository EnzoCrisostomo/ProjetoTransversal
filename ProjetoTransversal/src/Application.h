#pragma once
#include "Renderers/MasterRenderer.h"
#include "States/States.h"
#include <memory>
#include <GLFW/glfw3.h>

class PlayingState;

class Application
{
public:
	Application(const char* applicationName, int width, int height);
	~Application();
	void runLoop();
	void setup();
	void ChangeState(BaseState* state);

private:
	MasterRenderer* m_masterRenderer = nullptr;
	BaseState* m_activeState = nullptr;

	GLFWwindow* m_window = nullptr;
	int m_heigth, m_width;
	double m_elapsedTime;
	bool m_hasToClose = false;
};