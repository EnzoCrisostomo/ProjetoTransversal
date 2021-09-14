#pragma once
#include <array>
#include "ChunkMesh.h"
#include <glm/gtc/type_ptr.hpp>
#include "Options/Options.h"
#include "Block.h"

class World;

class Chunk
{
public:
	Chunk(World& world, int x = 0, int y = 0, int z = 0);

	~Chunk();

	ChunkMesh& GetMesh();
	glm::vec3 GetLocation() const;
	const BlockId GetBlock(int x, int y, int z) const;
	const BlockId GetBlock(const glm::ivec3& position) const;
	const bool HasMesh() const;

	void SetBlock(int x, int y, int z, BlockId block);
	void BuildMesh();

private:
	const bool OutOfBounds(int value) const;
	const int GetIndex(int x, int y, int z) const;
	
	const glm::ivec3 GetGlobalPosition(int x, int y, int z) const;

	World& m_world;
	std::array<BlockId, Options::chunkVolume> m_chunkData;
	ChunkMesh m_mesh;
	glm::vec3 m_position;
	bool m_hasMesh;
};