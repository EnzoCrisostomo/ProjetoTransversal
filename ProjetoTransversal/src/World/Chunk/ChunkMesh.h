#pragma once

#include "OpenGL/Model.h"
#include <glm/glm.hpp>

class ChunkMesh
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

	void AddWaterBlockFace(const std::vector<GLfloat>& blockFace,
						   const std::vector<GLfloat>& textureCoords,
						   const glm::ivec3& chunkPosition,
						   const glm::ivec3& blockPosition);

	void BufferMesh();

	const Model& GetBlocksModel() const;
	const Model& GetVegetationModel() const;
	const Model& GetWaterModel() const;

private:
	Mesh m_blocksMesh;
	Model m_blocksModel;
	GLuint m_blocksIndicesCount = 0;

	Mesh m_vegetationMesh;
	Model m_vegetationModel;
	GLuint m_vegetationIndicesCount = 0;
	
	Mesh m_waterMesh;
	Model m_waterModel;
	GLuint m_waterIndicesCount = 0;
};

