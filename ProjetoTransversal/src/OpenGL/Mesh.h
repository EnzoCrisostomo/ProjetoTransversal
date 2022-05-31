#pragma once
#include <vector>

struct Mesh
{
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> textureCoordinates;
	std::vector<GLuint>  indices;
	std::vector<GLfloat>  lightValues;

	void Free() 
	{
		vertexPositions.clear();
		textureCoordinates.clear();
		indices.clear();
		lightValues.clear();
		vertexPositions.shrink_to_fit();
		textureCoordinates.shrink_to_fit();
		indices.shrink_to_fit();
		lightValues.shrink_to_fit();
	}
};