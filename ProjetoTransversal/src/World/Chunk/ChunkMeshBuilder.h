#pragma once
#include <vector>
#include <glad/glad.h>
#include "World/Block/BlockDatabase.h"

class Chunk;
class ChunkMesh;
struct AdjacentBlocks;
enum class BlockId;

class ChunkMeshBuilder
{
public:
	ChunkMeshBuilder() = default;
	void BuildMesh(Chunk& chunk);
private:
	void TryToAddBlock(const BlockId& block, const glm::ivec3& position, const AdjacentBlocks& adjacentBlocks);
	void TryToAddFace(const BlockId& blockId, const std::vector<GLfloat>& blockFace, const std::vector<GLfloat>& textureCoords,
					  const glm::ivec3& blockPosition, const glm::ivec3& blockFacing);
	bool ShouldMakeFace(const BlockId& blockId, const glm::ivec3& blockFacing);

	Chunk* m_chunk = nullptr;
	ChunkMesh* m_chunkMesh = nullptr;
};

