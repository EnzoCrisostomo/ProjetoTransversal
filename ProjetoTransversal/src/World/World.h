#pragma once
#include <queue>
#include <unordered_map>
#include "Chunk/ChunkManager.h"

class MasterRenderer;
class Player;

class World
{
public:
	World(Player& player, std::string worldName);
	~World();

	void RenderWorld(MasterRenderer* masterRender);
	void UpdateWorld(const Player& player);
	void SetBlock(const glm::ivec3& position, BlockId blockId);
	BlockId GetBlock(const glm::ivec3& position);
	const int GetSeed() const;

private:
	bool LoadFromFile();
	bool SaveInFile();

	const bool OutOfBounds  (VectorXZ chunkPos, int y) const;
	const bool OutOfBoundsXZ(VectorXZ chunkPos) const;
	const bool OutOfBoundsY (int y) const;
	void BuildMesh();
	void SpiralAroundPlayer(const VectorXZ playerChunkPos);

	glm::ivec3 m_gizmo;
	VectorXZ m_oldPlayerPos;
	int m_seed;

	std::string m_name;
	std::string m_worldPath;
	Player* m_playerPont;

	ChunkManager m_chunkManager;	
	std::vector<VectorXZ> m_columnsPositionsInLoadDistance;
	std::vector<VectorXZ> m_columnsPositionsInViewDistance;
};