#pragma once
#include <vector>
#include "Vertex.h"

struct Mesh
{
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> textureCoordinates;
	std::vector<GLfloat> lightValues;
	std::vector<GLuint>  indices;
	std::vector<Vertex>  vertices;

	void Free() 
	{
		vertexPositions.clear();
		textureCoordinates.clear();
		lightValues.clear();
		indices.clear();
		vertices.clear();

		vertexPositions.shrink_to_fit();
		textureCoordinates.shrink_to_fit();
		lightValues.shrink_to_fit();
		indices.shrink_to_fit();
		vertices.shrink_to_fit();
	}
};