#include "ChunkManager.h"
#include "World/World.h"


ChunkManager::ChunkManager(World& world)
	: m_world(world)
{
}

ChunkManager::~ChunkManager()
{
}

ChunkColumn& ChunkManager::GetChunk(int x, int z)
{
	return GetChunk(VectorXZ{ x, z });
}

ChunkColumn& ChunkManager::GetChunk(VectorXZ pos)
{
	return m_chunkColumns.at(pos);
}

//Adiciona a chunk na tabela hash, contruindo no lugar de memória 
//onde ela vai ficar para evitar cópias desnecessarias
void ChunkManager::LoadChunk(VectorXZ pos)
{
	//caso a chunk ja esteja carregada a funçao retorna
	if (ChunkIsLoaded(pos))
		return;

	VectorXZ regionPos = GetRegion(pos);
	Region* region = nullptr;

	if (RegionIsLoaded(regionPos))
	{
		region = &m_regions.at(regionPos);
	}
	else
	{
		m_regions.try_emplace(regionPos, regionPos);
		region = &m_regions.at(regionPos);
	}

	std::vector<std::pair<glm::ivec3, BlockId>> blocos;
	if (m_blocksToSet.find(pos) != m_blocksToSet.end())
	{
		blocos = m_blocksToSet.at(pos);

		//TODO maybe erase instead of clear vector
		//TODO Save blocksToSet in files
		m_blocksToSet.at(pos).clear();
	}

	m_chunkColumns.try_emplace(pos,m_world, pos, blocos, region);
}

//Overload da função LoadChunk com argumentos distribuidos de forma diferente
void ChunkManager::LoadChunk(int x, int z)
{
	return LoadChunk(VectorXZ{ x, z });
}

//Adiciona um bloco para a lista de blocos que pertencem a chunks não carregadas na memoria
void ChunkManager::AddToBlockQueue(VectorXZ chunkPos, std::pair<glm::ivec3, BlockId> blocksToSet)
{
	if (m_blocksToSet.find(chunkPos) == m_blocksToSet.end())
	{
		m_blocksToSet[chunkPos] = std::vector<std::pair<glm::ivec3, BlockId>>();
	}

	//Move to ChunkManager 
	m_blocksToSet.at(chunkPos).push_back(blocksToSet);
}

//Deleta a chunk do hashMap para liberar memoria
void ChunkManager::UnloadChunk(VectorXZ pos)
{
	if (ChunkIsLoaded(pos))
		m_chunkColumns.erase(pos);
}

//Overload de UnloadChunk com argumentos separados
void ChunkManager::UnloadChunk(int x, int z)
{
	return UnloadChunk(VectorXZ{ x, z });
}

//Descarrega chunks que estão longe do jogador
void ChunkManager::UnloadFarChunks(VectorXZ playerChunkPos)
{
	int maxDistX = playerChunkPos.x + Options::loadDistance + 2;
	int maxDistZ = playerChunkPos.z + Options::loadDistance + 2;
	int minDistX = playerChunkPos.x - Options::loadDistance + 2;
	int minDistZ = playerChunkPos.z - Options::loadDistance + 2;

	VectorXZ maxDist = playerChunkPos + Options::loadDistance + 2;
	VectorXZ minDist = playerChunkPos - Options::loadDistance + 2;

	UnloadChunks(maxDist, minDist);

	VectorXZ maxRegion = GetRegion(VectorXZ{ maxDistX, maxDistZ });
	VectorXZ minRegion = GetRegion(VectorXZ{ minDistX, minDistZ });

	UnloadRegions(maxRegion, minRegion);

	return;
}

//Verifica se a chunk está carregada
const bool ChunkManager::ChunkIsLoaded(VectorXZ pos) const
{
	return m_chunkColumns.find(pos) != m_chunkColumns.end();
}

//Verifica se os vizinhos da chunks estão carregados
const bool ChunkManager::NeighborsAreLoaded(VectorXZ chunkPos) const
{
	VectorXZ neighbor1 = { chunkPos.x - 1, chunkPos.z	  };
	VectorXZ neighbor2 = { chunkPos.x    , chunkPos.z - 1 };
	VectorXZ neighbor3 = { chunkPos.x + 1, chunkPos.z	  };
	VectorXZ neighbor4 = { chunkPos.x    , chunkPos.z + 1 };
	if (!ChunkIsLoaded(neighbor1))
		return false;
	if (!ChunkIsLoaded(neighbor2))
		return false;
	if (!ChunkIsLoaded(neighbor3))
		return false;
	if (!ChunkIsLoaded(neighbor4))
		return false;

	return true;
}

void ChunkManager::UnloadRegion(VectorXZ pos)
{
	if (m_regions.find(pos) != m_regions.end())
	{
		m_regions.erase(pos);
	}
}

const bool ChunkManager::RegionIsLoaded(VectorXZ pos) const
{
	return m_regions.find(pos) != m_regions.end();
}

void ChunkManager::UnloadChunks(VectorXZ maxDist, VectorXZ minDist)
{
	for (auto& column : m_chunkColumns)
	{
		if (column.first.x > maxDist.x || column.first.x < minDist.x || 
			column.first.z > maxDist.z || column.first.z < minDist.z)
		{
			UnloadChunk(column.first);
			return UnloadChunks(maxDist, minDist);
		}
	}
	return;
}

void ChunkManager::UnloadRegions(VectorXZ maxRegion, VectorXZ minRegion)
{
	for (auto& region : m_regions)
	{
		if (region.first.x > maxRegion.x || region.first.x < minRegion.x || 
			region.first.z > maxRegion.z || region.first.z < minRegion.z)
		{
			UnloadRegion(region.first);
			return UnloadRegions(maxRegion, minRegion);
		}
	}
	return;
}

VectorXZ ChunkManager::GetRegion(const VectorXZ& chunkPos) const
{
	return VectorXZ({static_cast<int>(floor(static_cast<float>(chunkPos.x) / Options::regionSize)),
					 static_cast<int>(floor(static_cast<float>(chunkPos.z) / Options::regionSize)) });
}
