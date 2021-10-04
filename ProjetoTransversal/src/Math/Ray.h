#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
	Ray(const glm::vec3& position, const glm::vec3& direction);

	void Step(float scale);

	const glm::vec3& GetEnd() const;

	float GetLenght() const;

private:
	glm::vec3 m_rayStart;
	glm::vec3 m_rayEnd;
	glm::vec3 m_direction;
};