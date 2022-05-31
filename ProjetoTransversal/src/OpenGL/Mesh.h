#pragma once
#include <vector>

struct Mesh
{
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> textureCoordinates;
	std::vector<GLfloat> lightValues;
	std::vector<GLuint>  indices;

	void Free() 
	{
		vertexPositions.clear();
		textureCoordinates.clear();
		lightValues.clear();
		indices.clear();

		vertexPositions.shrink_to_fit();
		textureCoordinates.shrink_to_fit();
		lightValues.shrink_to_fit();
		indices.shrink_to_fit();
	}
};