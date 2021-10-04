#pragma once
#include <queue>
#include <unordered_map>
#include "Chunk/ChunkManager.h"

class MasterRenderer;
class Player;

class World
{
public:
	World(Player& player);
	~World();

	void RenderWorld(MasterRenderer* masterRender);
	void UpdateWorld(const Player& player);
	void SetBlock(const glm::ivec3& position, BlockId blockId);
	BlockId GetBlock(const glm::ivec3& position);
	const int GetSeed() const;

private:
	const bool OutOfBounds  (VectorXZ chunkPos, int y) const;
	const bool OutOfBoundsXZ(VectorXZ chunkPos) const;
	const bool OutOfBoundsY (int y) const;
	void BuildMesh();
	void SpiralAroundPlayer(const VectorXZ playerChunkPos);

	glm::ivec3 m_gizmo;
	VectorXZ m_oldPlayerPos;
	int m_seed;

	ChunkManager m_chunkManager;	
	std::vector<VectorXZ> m_columnsPositionsInLoadDistance;
	std::vector<VectorXZ> m_columnsPositionsInViewDistance;
};