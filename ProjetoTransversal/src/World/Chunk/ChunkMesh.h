#pragma once

#include "OpenGL/Chunk/BlockModel.h"
#include <glm/glm.hpp>

class ChunkMesh
{
public:
	ChunkMesh() = default;
	~ChunkMesh();


	void AddBlockFace(const std::vector<GLfloat>& blockFace,
					  const uint8_t& textureIndex,
					  const glm::ivec3& blockPosition);

	void AddVegetationBlock(const uint8_t& textureIndex,
							const glm::ivec3& blockPosition);

	void AddWaterBlockFace(std::vector<GLfloat> blockFace,
						   const uint8_t& textureIndex,
						   const glm::ivec3& blockPosition,
						   const bool isUpper);

	void BufferMesh();

	const BlockModel& GetBlocksModel() const;
	const BlockModel& GetVegetationModel() const;
	const BlockModel& GetWaterModel() const;

	const bool HasVegetation() const { return m_hasVegetation; }
	const bool HasWater() const { return m_hasWater; }

private:
	ChunkVertex MountVertex(const std::vector<GLfloat> &blockFace,
							  const uint8_t& textureIndex,
							  const glm::ivec3& blockPosition,
							  int &i,
							  int &index) const;

	bool m_hasVegetation = false;
	bool m_hasWater = false;

	BlockMesh m_blocksMesh;
	BlockModel m_blocksModel;
	GLuint m_blocksIndicesCount = 0;

	BlockMesh m_vegetationMesh;
	BlockModel m_vegetationModel;
	GLuint m_vegetationIndicesCount = 0;
	
	BlockMesh m_waterMesh;
	BlockModel m_waterModel;
	GLuint m_waterIndicesCount = 0;
};

