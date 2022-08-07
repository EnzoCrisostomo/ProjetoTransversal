#pragma once
#include "Math/Vectors.h"
#include "World/Block/BlockDatabase.h"
#include "Options/Options.h"

#include <GLFW/glfw3.h>

class World;
class PlayingState;

struct Dimensions
{
	Dimensions(glm::dvec3 dimensions)
	{
		this->sides = dimensions.x;
		this->top = dimensions.y;
		this->bottom = dimensions.z;
	}

	double sides;
	double top;
	double bottom;
};

class Player
{
public:
	Player();

	void Update(World* world, GLFWwindow* window, double elapsedTime);
	void SetPosition(glm::dvec3 newPos);
	void SetCamera(glm::dvec3 newPos);


	void CreateProjectionMatrix();
	const glm::dmat4& GetProjectionMatrix() const { return Options::teste ? m_projectionMatrix : m_projectionMatrixZoom; }
	const glm::dmat4& GetViewMatrix() const { return m_viewMatrix; }
	const glm::dvec3& GetPosition() const { return m_position; }
	const glm::dvec3& GetCameraFront() const { return m_cameraFront; }
	const Dimensions& GetDimensions() const { return m_dimensions; }

private:
	void PlaceAndBreakBlocks(GLFWwindow* window, World* world);
	bool CollidingWithBlock(const glm::ivec3 blockPos) const;
	void CheckCollision(World* world, const glm::dvec3 vel);
	void NewCollisionDetect(World* world, glm::dvec3 velocity);

	double m_elapsedTime;
	float m_speed;
	bool m_isGrounded;
	int m_gamemode;

	glm::dvec3 m_cameraFront;
	glm::dvec3 m_cameraUp;

	glm::dvec3 m_position;
	glm::dvec3 m_velocity;
	glm::dvec3 m_acceleration;

	Dimensions m_dimensions;
		 
	glm::dmat4 m_projectionMatrix;
	glm::dmat4 m_projectionMatrixZoom;
	glm::dmat4 m_viewMatrix;

	const bool Pular(GLFWwindow* window) const;
	glm::dvec3 HandleKeyboardInput(GLFWwindow* window);
	void HandleMouseInput(GLFWwindow* window);
	void HandleMovement(World* world, glm::dvec3 direction);
	const bool WillBreakBlock(GLFWwindow* window) const;
	const bool WillPlaceBlock(GLFWwindow* window) const;
	const bool WillGetBlock(GLFWwindow* window, BlockId block) const;
	const BlockId getBlockHoldingId() const;
};