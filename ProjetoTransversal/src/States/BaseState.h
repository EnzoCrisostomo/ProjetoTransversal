#pragma once
class Application;
class MasterRenderer;

class BaseState
{
public:
	BaseState(Application* app)
		: m_application(app){}

	virtual void Update(double elapsedTime) = 0;
	virtual void Render(MasterRenderer* renderer) = 0;

protected:
	Application* m_application;
};