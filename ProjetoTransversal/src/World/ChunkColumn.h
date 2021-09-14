#pragma once
#include <vector>
#include <queue>
#include "Chunk.h"
#include "VectorXZ.h"
#include "Renderers/MasterRenderer.h"

class World;

class ChunkColumn
{
public:
	ChunkColumn(World& world, VectorXZ position, std::vector<std::pair<glm::ivec3, BlockId>> blocksToSet);
	~ChunkColumn();

	BlockId GetBlock(const glm::ivec3& position) const;
	Chunk& GetChunk(int y);

	void SetBlock(int x, int y, int z, BlockId block);
	void SetBlock(const glm::ivec3& position, BlockId block);

	void RenderColumn(MasterRenderer* renderer);
	bool BuildMesh();
	bool HasFullMesh();
private:
	bool OutOfBounds(int x, int y, int z) const;

	World& m_world;
	VectorXZ m_position;
	std::vector<Chunk> m_chunks;
};

