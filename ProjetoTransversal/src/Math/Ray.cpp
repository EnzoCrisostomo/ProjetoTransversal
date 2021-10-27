#include "Ray.h"

Ray::Ray(const glm::vec3& position, const glm::vec3& direction) :
	m_rayStart(position), m_rayEnd(position), m_direction(direction)
{
}

void Ray::Step(float scale)
{
	m_rayEnd += m_direction * scale;
	return;
}

const glm::vec3& Ray::GetEnd() const
{
	return m_rayEnd;
}

float Ray::GetLenght() const
{
	return glm::distance(m_rayStart, m_rayEnd);
}
