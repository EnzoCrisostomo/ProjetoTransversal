#include "World.h"
#include "Renderers/MasterRenderer.h"
#include "Player/Player.h"
#include <limits>

namespace
{
	VectorXZ GetChunkPos(const glm::ivec3& position)
	{
		double fPosX = static_cast<double>(position.x);
		double fPosZ = static_cast<double>(position.z);
		int chunkX  = static_cast<int>(floor(fPosX / Options::chunkSize));
		int chunkZ  = static_cast<int>(floor(fPosZ / Options::chunkSize));
		return { chunkX, chunkZ };
	}

	glm::ivec3 GetBlockPos(const glm::ivec3& position)
	{
		int modX = position.x % Options::chunkSize;
		if (modX < 0)
			modX += Options::chunkSize;

		int modZ = position.z % Options::chunkSize;
		if (modZ < 0)
			modZ += Options::chunkSize;

		return { modX, position.y, modZ };
	}
}

World::World(Player& player)
	: m_chunkManager(*this)
{
	int chunkPlayerX = static_cast<int>(floor(player.GetPosition().x / Options::chunkSize));
	int chunkPlayerZ = static_cast<int>(floor(player.GetPosition().z / Options::chunkSize));

	srand((unsigned)time(0));

	m_seed = 1337;//(rand() % std::numeric_limits<int>::max()) + 1;

	m_oldPlayerPos = { chunkPlayerX, chunkPlayerZ };

	SpiralAroundPlayer({ chunkPlayerX, chunkPlayerZ });
}

World::~World()
{
	std::cout << "World destroyed!\n";
}

//Checa para ver se a posição existe no mundo
const bool World::OutOfBounds(VectorXZ chunkPos, int y) const
{
	if (y < 0 || y >= Options::chunkSize * Options::chunkColumnHeigth)
		return true;
	if (!m_chunkManager.ChunkIsLoaded(chunkPos))
		return true;

	return false;
}

const bool World::OutOfBoundsXZ(VectorXZ chunkPos) const
{
	if (!m_chunkManager.ChunkIsLoaded(chunkPos))
		return true;

	return false;
}

const bool World::OutOfBoundsY(int y) const
{
	if (y < 0 || y >= Options::chunkSize * Options::chunkColumnHeigth)
		return true;

	return false;
}

//Constroi a mesh da proxima chunk da fila, caso todas as chunks
//ja tenham sido construidas remove a posicao da fila
void World::BuildMesh()
{
	for (int i = 0; i < m_columnsPositionsInViewDistance.size(); i++)
	{
		VectorXZ pos = m_columnsPositionsInViewDistance.at(i);
		if (!m_chunkManager.ChunkIsLoaded(pos))
			continue;
		if (!m_chunkManager.NeighborsAreLoaded(pos))
			continue;
		ChunkColumn& coluna = m_chunkManager.GetChunk(pos);
		if (coluna.HasFullMesh())
			continue;

		coluna.BuildMesh();
		break;
	}
}

void World::SpiralAroundPlayer(const VectorXZ playerChunkPos)
{
	//Loop para determinar quais chunks estao na viewDistance e na loadDistance
	int maxIterations = static_cast<int>(pow(Options::loadDistance * 2, 2));
	unsigned layer = 1;
	unsigned leg = 0;
	int x = 0;
	int z = 0;

	for (int i = 0; i < maxIterations; i++)
	{
		if (i != 0)
			switch (leg)
			{
			case 0: ++x; if (x == layer)  ++leg;                break;
			case 1: ++z; if (z == layer)  ++leg;                break;
			case 2: --x; if (-x == layer)  ++leg;                break;
			case 3: --z; if (-z == layer) { leg = 0; ++layer; } break;
			}
		int result = abs(z) + abs(x);
		//Load distance
		if (result > Options::loadDistance + (Options::loadDistance / 2))
			continue;

		VectorXZ pos = { playerChunkPos.x + x, playerChunkPos.z + z };
		m_columnsPositionsInLoadDistance.push_back(pos);

		//View distance
		if (abs(z) > Options::viewDistance || abs(x) > Options::viewDistance)
			continue;
		if (result > Options::viewDistance + (Options::viewDistance / 2))
			continue;
		m_columnsPositionsInViewDistance.push_back(pos);
	}
}

//adiciona todas colunas para o vetor de renderizacao onde
//todo o mundo carregado sera renderizado
void World::RenderWorld(MasterRenderer* masterRender)
{
	//TODO Fix this lul
	for (int i = 0; i < 8; i++)
		BuildMesh();

	/*if (m_chunkColumns.empty())
		return;*/

	for (auto& column : m_columnsPositionsInViewDistance)
	{
		if (!m_chunkManager.ChunkIsLoaded(column))
			continue;
		if (!m_chunkManager.GetChunk(column).HasFullMesh())
			continue;
		m_chunkManager.GetChunk(column).RenderColumn(masterRender);
	}
	masterRender->DrawCube(m_gizmo);
}

//atualiza o estado do mundo, removendo colunas antigas fora do limite e
//adicionando colunas novas que estao dentro do limite
void World::UpdateWorld(const Player& player)
{
	int chunkPlayerX = static_cast<int>(floor(player.GetPosition().x / Options::chunkSize));
	int chunkPlayerZ = static_cast<int>(floor(player.GetPosition().z / Options::chunkSize));
	VectorXZ playerChunkPos = { chunkPlayerX, chunkPlayerZ };
	if (m_oldPlayerPos != playerChunkPos)
	{
		m_columnsPositionsInViewDistance.clear();
		m_columnsPositionsInLoadDistance.clear();
		SpiralAroundPlayer(playerChunkPos);
		m_chunkManager.UnloadFarChunks(playerChunkPos);

		m_oldPlayerPos = playerChunkPos;
	}

	for (auto& coluna : m_columnsPositionsInLoadDistance)
	{
		if (m_chunkManager.ChunkIsLoaded(coluna))
			continue;

		m_chunkManager.LoadChunk(coluna);
		break;
	}
}
void World::SetBlock(const glm::ivec3& position, BlockId blockId)
{
	VectorXZ chunkPos = GetChunkPos(position);

	if (OutOfBoundsY(position.y))
		return;
	//TODO lista de blocos que precisam ser setados em chunks não existentes
	if (OutOfBoundsXZ(chunkPos))
	{
		m_chunkManager.AddToBlockQueue(chunkPos, std::pair<glm::ivec3, BlockId>(GetBlockPos(position), blockId));
		return;
	}

	glm::ivec3 blockPos = GetBlockPos(position);
	m_chunkManager.GetChunk(chunkPos).SetBlock(blockPos, blockId);

	//TODO limpar código
	//Rebuild neighbor mesh if in chunk border
	VectorXZ neighbor1 = { chunkPos.x - 1, chunkPos.z };
	VectorXZ neighbor2 = { chunkPos.x    , chunkPos.z - 1 };
	VectorXZ neighbor3 = { chunkPos.x + 1, chunkPos.z };
	VectorXZ neighbor4 = { chunkPos.x    , chunkPos.z + 1 };
	//Horizontal
	if (blockPos.x == 0)
		if (!OutOfBounds(neighbor1, position.y))
			if(m_chunkManager.GetChunk(neighbor1).GetChunk(blockPos.y / Options::chunkSize).HasMesh())
				m_chunkManager.GetChunk(neighbor1).GetChunk(blockPos.y / Options::chunkSize).BuildMesh();
	if (blockPos.z == 0)
		if (!OutOfBounds(neighbor2, position.y))
			if (m_chunkManager.GetChunk(neighbor2).GetChunk(blockPos.y / Options::chunkSize).HasMesh())
				m_chunkManager.GetChunk(neighbor2).GetChunk(blockPos.y / Options::chunkSize).BuildMesh();
	if (blockPos.x == 15)
		if (!OutOfBounds(neighbor3, position.y))
			if (m_chunkManager.GetChunk(neighbor3).GetChunk(blockPos.y / Options::chunkSize).HasMesh())
				m_chunkManager.GetChunk(neighbor3).GetChunk(blockPos.y / Options::chunkSize).BuildMesh();
	if (blockPos.z == 15)
		if (!OutOfBounds(neighbor4, position.y))
			if (m_chunkManager.GetChunk(neighbor4).GetChunk(blockPos.y / Options::chunkSize).HasMesh())
				m_chunkManager.GetChunk(neighbor4).GetChunk(blockPos.y / Options::chunkSize).BuildMesh();

	//Vertical
	if ((blockPos.y % Options::chunkSize) == 0)
		if (!OutOfBounds(chunkPos, position.y - Options::chunkSize))
			if (m_chunkManager.GetChunk(chunkPos).GetChunk((blockPos.y / Options::chunkSize) - 1).HasMesh())
				m_chunkManager.GetChunk(chunkPos).GetChunk((blockPos.y / Options::chunkSize) - 1).BuildMesh();
	if ((blockPos.y % Options::chunkSize) == 15)
		if (!OutOfBounds(chunkPos, position.y + Options::chunkSize))
			if (m_chunkManager.GetChunk(chunkPos).GetChunk((blockPos.y / Options::chunkSize) + 1).HasMesh())
				m_chunkManager.GetChunk(chunkPos).GetChunk((blockPos.y / Options::chunkSize) + 1).BuildMesh();

	return;
}

BlockId World::GetBlock(const glm::ivec3& position)
{
	VectorXZ chunkPos = GetChunkPos(position);

	if (OutOfBounds(chunkPos, position.y))
		return BlockId::Air;

	glm::ivec3 blockPos = GetBlockPos(position);

	return m_chunkManager.GetChunk(chunkPos).GetBlock(blockPos);
}

const int World::GetSeed() const
{
	return m_seed;
}