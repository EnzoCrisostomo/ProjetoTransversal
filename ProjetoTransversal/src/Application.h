#pragma once
#include "Renderers/MasterRenderer.h"
#include <GLFW/glfw3.h>

class PlayingState;
class MainMenuState;

enum class State : uint8_t
{
	Menu,
	Playing,
	
	StateCount
};

class Application
{
public:
	Application(const char* applicationName, int width, int height);
	~Application();
	void runLoop();
	void setup();
	void ChangeState(State state);
private:
	MasterRenderer* m_masterRenderer = nullptr;

	PlayingState* m_playingState = nullptr;
	MainMenuState* m_mainMenuState = nullptr;

	GLFWwindow* m_window = nullptr;
	int m_heigth, m_width;
	double m_elapsedTime;

	State m_state;
};