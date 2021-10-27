#pragma once
#include <vector>
#include <queue>
#include "World/Generation/Region.h"
#include "Chunk.h"
#include "Renderers/MasterRenderer.h"

class World;

class ChunkColumn
{
public:
	ChunkColumn(World& world, VectorXZ position, std::vector<std::pair<glm::ivec3, BlockId>> blocksToSet, Region* region);
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
	const glm::ivec3 GetGlobalPosition(int x, int y, int z) const;
	void TryToGenerateTree(int x, int y, int z);

	Region* m_region;
	World& m_world;
	VectorXZ m_position;
	std::vector<Chunk> m_chunks;
};

