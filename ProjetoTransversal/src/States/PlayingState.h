#pragma once
#include <string>

struct GLFWwindow;
class MasterRenderer;

namespace PlayingState
{
	void EnterState(GLFWwindow* window, std::string worldName);
	void Update(GLFWwindow* window, double elapsedTime);
	void Render(MasterRenderer* renderer);
	void LeaveState();

	void UpdateMatrix();
};