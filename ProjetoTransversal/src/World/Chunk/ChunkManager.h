#pragma once
#include <unordered_map>
#include "ChunkColumn.h"

class World;

class ChunkManager
{
public:
	ChunkManager(World& world);
	~ChunkManager();

	ChunkColumn& GetChunk(int x, int z);
	ChunkColumn& GetChunk(VectorXZ pos);
	void LoadChunk(VectorXZ pos);
	void LoadChunk(int x, int z);
	void AddToBlockQueue(VectorXZ chunkPos, std::pair<glm::ivec3, BlockId> blocksToSet);
	void UnloadChunk(VectorXZ pos);
	void UnloadChunk(int x, int z);
	void UnloadFarChunks(VectorXZ playerPos);
	const bool ChunkIsLoaded(VectorXZ pos) const;
	const bool NeighborsAreLoaded(VectorXZ chunkPos) const;

private:
	World& m_world;
	std::unordered_map<VectorXZ, ChunkColumn> m_chunkColumns;
	std::unordered_map<VectorXZ, std::vector<std::pair<glm::ivec3, BlockId>>> m_blocksToSet;
};

