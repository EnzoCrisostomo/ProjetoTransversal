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

	std::vector<std::pair<glm::ivec3, BlockId>> blocos;
	if (m_blocksToSet.find(pos) != m_blocksToSet.end())
	{
		blocos = m_blocksToSet.at(pos);
		m_blocksToSet.at(pos).clear();
	}

	m_chunkColumns.emplace(std::piecewise_construct,
		std::forward_as_tuple(pos),
		std::forward_as_tuple(m_world, pos, blocos));
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
void ChunkManager::UnloadFarChunks(VectorXZ playerPos)
{
	int maxDistX = playerPos.x + Options::loadDistance + 2;
	int maxDistZ = playerPos.z + Options::loadDistance + 2;
	int minDistX = playerPos.x - Options::loadDistance + 2;
	int minDistZ = playerPos.z - Options::loadDistance + 2;

	for (auto& column : m_chunkColumns)
	{
		if (column.first.x > maxDistX || column.first.x < minDistX)
		{
			UnloadChunk(column.first);
			return UnloadFarChunks(playerPos);
		}

		else if (column.first.z > maxDistZ || column.first.z < minDistZ)
		{
			UnloadChunk(column.first);
			return UnloadFarChunks(playerPos);
		}
	}
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
