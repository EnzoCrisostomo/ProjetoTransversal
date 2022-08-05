#pragma once
class Application;
class MasterRenderer;

struct GLFWwindow;

class BaseState
{
public:
	BaseState(Application* app)
		: m_application(app){}

	virtual void Update(GLFWwindow* window, double elapsedTime) = 0;
	virtual void Render(MasterRenderer* renderer) = 0;

protected:
	Application* m_application;
};