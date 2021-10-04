#include "Vectors.h"

glm::ivec3 Floor(const glm::vec3& pos)
{
	int x = static_cast<int>(floor(pos.x));
	int y = static_cast<int>(floor(pos.y));
	int z = static_cast<int>(floor(pos.z));
	return glm::ivec3(x, y, z);
}