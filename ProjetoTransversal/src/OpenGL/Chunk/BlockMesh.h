#pragma once
#include <vector>
#include "ChunkVertex.h"

struct BlockMesh
{
	std::vector<GLuint>  indices;
	std::vector<ChunkVertex>  vertices;

	void Free() 
	{
		indices.clear();
		vertices.clear();

		indices.shrink_to_fit();
		vertices.shrink_to_fit();
	}
};