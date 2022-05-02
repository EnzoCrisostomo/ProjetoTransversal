#pragma once

#include "OpenGL/Model.h"
#include <glm/glm.hpp>

class ChunkMesh : public Mesh
{
public:
	ChunkMesh() = default;
	~ChunkMesh();


	void AddBlockFace(const std::vector<GLfloat>& blockFace,
					  const std::vector<GLfloat>& textureCoords,
					  const glm::ivec3& chunkPosition,
					  const glm::ivec3& blockPosition);

	void AddVegetationBlock(const std::vector<GLfloat>& textureCoords,
					  const glm::ivec3& chunkPosition,
					  const glm::ivec3& blockPosition);

	void BufferMesh();

	const Model& GetModel() const;

private:
	GLuint m_indicesCount = 0;
	Model m_model;
};

