#pragma once
#include <vector>

struct Mesh
{
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> textureCoordinates;
	std::vector<GLuint>  indices;
};