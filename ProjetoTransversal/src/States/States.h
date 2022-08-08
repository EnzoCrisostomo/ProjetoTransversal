#pragma once
#include <cinttypes>
#include <vector>
#include "MenuButton.h"
#include "Player/Player.h"

class Application;
class MasterRenderer;
class World;
struct GLFWwindow;

//=================Base=================//
class BaseState
{
public:
	BaseState(Application* app, GLFWwindow* window)
		: m_application(app), m_window(window) {}

	virtual ~BaseState() = default;

	virtual void Update(double elapsedTime) = 0;
	virtual void Render(MasterRenderer* renderer) = 0;

protected:
	Application* m_application;
	GLFWwindow* m_window;
};


//=================Jogo=================//
class PlayingState : public BaseState
{
public:
	PlayingState(Application* app, GLFWwindow* window, std::string worldName);

	~PlayingState();

	void Update(double elapsedTime) override;
	void Render(MasterRenderer* renderer) override;

	void LeaveState();

private:
	World* m_world;
	Player m_player;
};


//=================Main Menu=================//
class MainMenuState : public BaseState
{
public:
	MainMenuState(Application* app, GLFWwindow* window);
	~MainMenuState();

	void Update(double elapsedTime) override;
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