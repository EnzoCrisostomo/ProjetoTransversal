#include "ChunkColumn.h"
#include "World.h"
#include "Options/Options.h"
#include <math.h>
#include <random>

ChunkColumn::ChunkColumn(World& world, VectorXZ position, std::vector<std::pair<glm::ivec3, BlockId>> blocksToSet )
	: m_world(world), m_position(position)
{
	//cria as chunks e preenche com blocos de ar
	m_chunks.reserve(Options::chunkColumnHeigth);
	for (int y = 0; y < Options::chunkColumnHeigth; y++)
		m_chunks.emplace_back(m_world, m_position.x, y, m_position.z);


	//loops para inserir os blocos de acordo com o mapa de altura da coluna
	for (size_t y = 0; y < Options::chunkColumnHeigth * Options::chunkSize; y++)
	for (size_t x = 0; x < Options::chunkSize; x++)
	for (size_t z = 0; z < Options::chunkSize; z++)
	{		
		if (y > 40)
			continue;
		//Altura igual ao mapa de altura
		if (y == 40)
		{
			if (x == 0 || z == 0 || x == 15 || z == 15)
				SetBlock(x, y, z, BlockId::Sand);
			else
				SetBlock(x, y, z, BlockId::Grass);
		}
		//Altura até 5 blocos a baixo do mapa de altura
		else if (y > 35)
		{
			if (x == 0 || z == 0 || x == 15 || z == 15)
				SetBlock(x, y, z, BlockId::Sand);
			else
				SetBlock(x, y, z, BlockId::Dirt);
		}
		//Demais blocos abaixo
		else
			SetBlock(x, y, z, BlockId::Stone);
	}
	//Insere os blocos de uma lista de bloco que foram setados
	//enquanto a chunk não estava carregada
	for (auto& block : blocksToSet)
	{
		SetBlock(block.first, block.second);
	}
}

//Destrutor
ChunkColumn::~ChunkColumn()
{
}

//retorna o id do bloco da posicao dada
BlockId ChunkColumn::GetBlock(const glm::ivec3& position) const
{
	//caso esteja fora dos limites retorna um bloco de ar
	if (OutOfBounds(position.x, position.y, position.z))
		return BlockId::Air;
	int chunkY = position.y / Options::chunkSize;
	int blockY = position.y % Options::chunkSize;

	return m_chunks[chunkY].GetBlock(position.x, blockY, position.z);
}

//Retorna a chunk na posicao y
Chunk& ChunkColumn::GetChunk(int y)
{
	return m_chunks[y];
}

//Muda o bloco na posição(x, y, z) da chunkColumn
void ChunkColumn::SetBlock(int x, int y, int z, BlockId block)
{
	if (OutOfBounds(x, y, z))
		return;

	m_chunks.at(y / Options::chunkSize).SetBlock(x, y % Options::chunkSize, z, block);
}

//Muda o bloco na posição(x, y, z) da chunkColumn
void ChunkColumn::SetBlock(const glm::ivec3& position, BlockId block)
{
	SetBlock(position.x, position.y, position.z, block);
	return;
}

//renderiza a mesh de todas as chunks da coluna
void ChunkColumn::RenderColumn(MasterRenderer* renderer)
{
	for (int y = 0; y < m_chunks.size(); y++)
		renderer->DrawChunk(m_chunks[y].GetMesh());
}

//constroi a mesh de uma chunk da coluna que ainda não foi construida
bool ChunkColumn::BuildMesh()
{
	//caso tenha a mesh completa retorn sem fazer nada
	if (HasFullMesh())
		return true;

	//Construi uma chunkmesh por frame para melhorar o FPS
	for (Chunk& chunk : m_chunks)
	{
		if (!chunk.HasMesh())
		{
			chunk.BuildMesh();
			break;
		}
	}

	return false;
}

//Checa para ver se todas chunks tem uma mesh
bool ChunkColumn::HasFullMesh()
{
	for (Chunk& chunk : m_chunks)
	{
		if (!chunk.HasMesh())
			return false;
	}
	return true;
}

//checa para ver se a posicao é valida
bool ChunkColumn::OutOfBounds(int x, int y, int z) const
{
	if (x < 0 || y < 0 || z < 0		||
		x >= Options::chunkSize		||
		z >= Options::chunkSize		||
		y >= Options::chunkColumnHeigth * Options::chunkSize)
		return true;
	else
		return false;
}
