#pragma once

#include "Player.h"
#include <GLFW/glfw3.h>
#include "World/World.h"
#include "Renderers/MasterRenderer.h"
class Application
{
public:
	Application(const char* applicationName, int width, int height);
	~Application();
	void runLoop();
private:
	Player m_player;

	World* m_world;
	MasterRenderer* m_masterRenderer;

	GLFWwindow* m_window;
	int m_heigth, m_width;
	double m_elapsedTime;
};


