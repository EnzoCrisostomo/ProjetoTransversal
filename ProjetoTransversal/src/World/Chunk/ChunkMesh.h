#pragma once

#include "OpenGL/Model.h"
#include <glm/glm.hpp>

class ChunkMesh
{
public:
	ChunkMesh() = default;
	~ChunkMesh();


	void AddBlockFace(const std::vector<GLfloat>& blockFace,
					  const uint8_t& textureIndex,
					  const glm::ivec3& chunkPosition,
					  const glm::ivec3& blockPosition);

	void AddVegetationBlock(const uint8_t& textureIndex,
							const glm::ivec3& chunkPosition,
							const glm::ivec3& blockPosition);

	void AddWaterBlockFace(std::vector<GLfloat> blockFace,
						   const uint8_t& textureIndex,
						   const glm::ivec3& chunkPosition,
						   const glm::ivec3& blockPosition,
						   const bool isUpper);

	void BufferMesh();

	const Model& GetBlocksModel() const;
	const Model& GetVegetationModel() const;
	const Model& GetWaterModel() const;

	const bool HasVegetation() const { return m_hasVegetation; }
	const bool HasWater() const { return m_hasWater; }

private:
	bool m_hasVegetation = false;
	bool m_hasWater = false;

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

