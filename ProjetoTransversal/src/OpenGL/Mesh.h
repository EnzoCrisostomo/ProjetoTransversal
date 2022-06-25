#pragma once
#include <vector>
#include "Vertex.h"

struct Mesh
{
	std::vector<GLuint>  indices;
	std::vector<Vertex>  vertices;

	void Free() 
	{
		indices.clear();
		vertices.clear();

		indices.shrink_to_fit();
		vertices.shrink_to_fit();
	}
};