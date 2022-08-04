#pragma once
#include "Math/Vectors.h"
#include "World/Block/BlockDatabase.h"
#include "Options/Options.h"

#include <GLFW/glfw3.h>

class World;

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
	Player(GLFWwindow* window);

	void Update(World* world, double elapsedTime);
	void SetWindow(GLFWwindow* window);
	void SetPosition(glm::dvec3 newPos);
	void SetCamera(glm::dvec3 newPos);

	const bool WillBreakBlock() const;
	const bool WillPlaceBlock() const;
	const bool WillGetBlock(BlockId block) const;
	const BlockId getBlockHoldingId() const;


	void CreateProjectionMatrix();
	const glm::dmat4& GetProjectionMatrix() const { return Options::teste ? m_projectionMatrix : m_projectionMatrixZoom; }
	const glm::dmat4& GetViewMatrix() const { return m_viewMatrix; }
	const glm::dvec3& GetPosition() const { return m_position; }
	const glm::dvec3& GetCameraFront() const { return m_cameraFront; }
	const Dimensions& GetDimensions() const { return m_dimensions; }

	bool m_shouldPause = false;
private:
	void PlaceAndBreakBlocks(World* world);
	bool CollidingWithBlock(const glm::ivec3 blockPos) const;
	void CheckCollision(World* world, const glm::dvec3 vel);
	void NewCollisionDetect(World* world, glm::dvec3 velocity);

	GLFWwindow* m_window;

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

	const bool Pular() const;
	glm::dvec3 HandleKeyboardInput();
	void HandleMouseInput();
	void HandleMovement(World* world, glm::dvec3 direction);
};