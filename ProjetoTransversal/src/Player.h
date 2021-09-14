#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
class Player
{
public:
	Player();

	void Update(GLFWwindow* window, double elapsedTime);

	void CreateProjectionMatrix();
	const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
	const glm::vec3& GetPosition() const { return m_position; }
	const glm::vec3& GetCameraFront() const { return m_cameraFront; }

private:
	GLFWwindow* m_window;
	double m_elapsedTime;
	float m_speed;
	int m_gamemode;

	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;

	glm::vec3 m_position;
	glm::vec3 m_rotation;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	void HandleKeyboardInput();
	void HandleMouseInput();
};

