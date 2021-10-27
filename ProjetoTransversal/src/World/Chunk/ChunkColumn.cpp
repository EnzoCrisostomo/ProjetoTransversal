#include "ChunkColumn.h"
#include "World/World.h"
#include "Options/Options.h"
#include "World/Generation/NoiseGenerator.h"
#include "World/Generation/WorldGen.h"
#include <math.h>
#include <random>

namespace
{
	VectorXZ GetRegion(const VectorXZ& chunkPos)
	{
		return VectorXZ({ static_cast<int>(floor(static_cast<float>(chunkPos.x) / Options::regionSize)),
						 static_cast<int>(floor(static_cast<float>(chunkPos.z) / Options::regionSize)) });
	}

	int getRegionIndex(VectorXZ pos)
	{
		VectorXZ chunkPosInRegion = { pos.x % Options::regionSize,
									  pos.z % Options::regionSize };
		if (chunkPosInRegion.x < 0)
			chunkPosInRegion.x += Options::regionSize;
		if (chunkPosInRegion.z < 0)
			chunkPosInRegion.z += Options::regionSize;

		return chunkPosInRegion.x + chunkPosInRegion.z * Options::regionSize;
	}

	std::streampos getFileStartIndex(int index)
	{
		return (static_cast<std::streampos>(index) * Options::chunkVolume * Options::chunkColumnHeigth * sizeof(BlockId)) + sizeof(uint64_t);
	}
}

ChunkColumn::ChunkColumn(World& world, VectorXZ position, std::vector<std::pair<glm::ivec3, BlockId>> blocksToSet, Region* region)
	: m_world(world), m_position(position), m_region(region)
{
	//cria as chunks e preenche com blocos de ar
	m_chunks.reserve(Options::chunkColumnHeigth);
	for (int y = 0; y < Options::chunkColumnHeigth; y++)
		m_chunks.emplace_back(m_world, *this, m_position.x, y, m_position.z);

	bool hasData = false;
	uint64_t regionHeader = 0;
	int regionIndex = getRegionIndex(m_position);
	if (Options::saveEnabled)
	{
		if (m_region->file->is_open())
		{
			m_region->file->seekg(0);
			m_region->file->read(reinterpret_cast<char*>(&regionHeader), sizeof(uint64_t));

			hasData = regionHeader & (uint64_t(1) << regionIndex);

			if (hasData)
			{
				std::streampos startPos = getFileStartIndex(regionIndex);
				m_region->file->seekg(startPos);
			for (auto& chunk : m_chunks)
			{
				auto& data = chunk.GetData();
					m_region->file->read(reinterpret_cast<char*>(data.data()), sizeof(BlockId) * Options::chunkVolume);
			}
				/*std::cout << "Estados Apos ler\n";
				std::cout << "Good: " << m_region->file->good() << "\n";
				std::cout << "Fail: " << m_region->file->fail() << "\n";
				std::cout << "Bad: " << m_region->file->bad() << "\n";*/
			}
		}
		else
		{
			std::cout << "Could not open file!\n";
		}
		myFile->close();
		delete myFile;
	}

	if (!hasData)
	{
	//cria o mapa de altura a partir de ruido (noise)
	//NoiseGenerator noiseGenerator(m_world.GetSeed());
	//std::array<int, Options::chunkArea> heigtMap = noiseGenerator.GenerateNoise(Options::chunkSize, Options::chunkSize, m_position);


	//std::cout << "Column pos: x[" << m_position.x << "], z[" << m_position.z << "]\n";

	//cria as chunks e preenche com blocos de ar

	auto chunkDataMap = WorldGen::GenerateChunk(m_world.GetSeed(), m_position);

	//loops para inserir os blocos de acordo com o mapa de altura da coluna
	for (int y = 0; y < Options::chunkColumnHeigth * Options::chunkSize; y++)
	for (int x = 0; x < Options::chunkSize; x++)
	for (int z = 0; z < Options::chunkSize; z++)
	{
		//int heigthXZ = heigtMap[x * Options::chunkSize + z];
			int heigthXZ = chunkDataMap[static_cast<size_t>(x) * Options::chunkSize + z].height;
			BlockId surfaceBlock = chunkDataMap[static_cast<size_t>(x) * Options::chunkSize + z].blockId;

		auto globalPos = GetGlobalPosition(x, y, z);

		//Altura maior que o mapa de altura
		if (y > heigthXZ)
		{
			if (y < Options::waterLevel)
				SetBlock(x, y, z, BlockId::Water);
			continue;
		}
		//Altura igual ao mapa de altura
		else if (y == heigthXZ)
		{
				/*if (x == 0 || z == 0 || x == Options::chunkSize-1 || z == Options::chunkSize - 1)
				SetBlock(x, y, z, BlockId::Sand);
			else*/
				SetBlock(x, y, z, surfaceBlock);
				bool anotherTree = false;
				for (int i = -2; i < 3; i++) 
				for (int j = -1; j < 3; j++) 
				for (int k = -2; k < 3; k++) 
					if (GetBlock({ x + i, y + j, z + k }) == BlockId::DarkWood || GetBlock({ x + i, y + j, z + k }) == BlockId::LightWood) 
						anotherTree = true;
				//TODO arvores por seed
				if (!anotherTree && y > Options::waterLevel)
					TryToGenerateTree(x, y, z);
		}
		//Altura até 5 blocos a baixo do mapa de altura
		else if (y > heigthXZ - 5)
		{
				/*if (x == 0 || z == 0 || x == Options::chunkSize - 1 || z == Options::chunkSize - 1)
				SetBlock(x, y, z, BlockId::Sand);
			else*/
				SetBlock(x, y, z, BlockId::Dirt);
		}
		//Demais blocos abaixo
		else
			if(y == 0)
				SetBlock(x, y, z, BlockId::Lava);
			else
			SetBlock(x, y, z, BlockId::Stone);
	}
		if (Options::saveEnabled)
		{
			regionHeader |= uint64_t(1) << regionIndex;
			m_region->file->seekp(0);
			m_region->file->write(reinterpret_cast<char*>(&regionHeader), sizeof(uint64_t));
		}
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
	if (Options::saveEnabled)
	{
		if (m_region->file->is_open())
		{
			/*std::cout << "Estados Antes\n";
			std::cout << "Good: " << m_region->file->good() << "\n";
			std::cout << "Fail: " << m_region->file->fail() << "\n";
			std::cout << "Bad: " << m_region->file->bad() << "\n";*/

			m_region->file->clear();
			/*std::cout << "==============\nRegion Pos: \n";
			m_region->position.Print();*/
			int regionIndex = getRegionIndex(m_position);
			std::streampos startPos = getFileStartIndex(regionIndex);
			m_region->file->seekp(startPos);
			for (auto& chunk : m_chunks)
			{
				auto& data = chunk.GetData();
				m_region->file->write(reinterpret_cast<char*>(data.data()), sizeof(BlockId) * Options::chunkVolume);
			}

			/*std::cout << "Estados escrever\n";
			std::cout << "Good: " << m_region->file->good() << "\n";
			std::cout << "Fail: " << m_region->file->fail() << "\n";
			std::cout << "Bad: " << m_region->file->bad() << "\n";*/
		}
		myFile->close();
		delete myFile;
	}
}

//retorna o id do bloco da posicao dada
BlockId ChunkColumn::GetBlock(const glm::ivec3& position) const
{
	//caso esteja fora dos limites retorna um bloco de ar
	if (OutOfBounds(position.x, position.y, position.z))
		return m_world.GetBlock(GetGlobalPosition(position.x, position.y, position.z));

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
		return m_world.SetBlock(GetGlobalPosition(x, y, z), block);

	m_chunks.at(y / Options::chunkSize).SetBlock(x, y % Options::chunkSize, z, block);
}

//Muda o bloco na posição(x, y, z) da chunkColumn
void ChunkColumn::SetBlock(const glm::ivec3& position, BlockId block)
{
	SetBlock(position.x, position.y, position.z, block);
	return;
}

//retorna a posicao do bloco em coordenadas globais
const glm::ivec3 ChunkColumn::GetGlobalPosition(int x, int y, int z) const
{
	return glm::ivec3(	m_position.x * Options::chunkSize + x,
															y,
						m_position.z * Options::chunkSize + z);
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

//tenta adicionar uma arvore no local
void ChunkColumn::TryToGenerateTree(int x, int y, int z)
{
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::uniform_int_distribution<> distr(0, 350);
	int number = distr(randomGenerator);
	if (number > 4 && number < 20)
	{
		for (int i = 1; i < number; i++)
		{
			if(number % 2 == 0)
				SetBlock(x, y + i, z, BlockId::DarkWood);
			else
				SetBlock(x, y + i, z, BlockId::LightWood);
		}
		for (int i =  number - 2; i < number + 1; i++)
		for (int j = -2; j <= 2; j++)
		for (int k = -2; k <= 2; k++)
		{
			if (GetBlock({ x + j, y + i, z + k }) == BlockId::Air)
			{
				int chunkY = (y + i) / Options::chunkSize;
				int blockY = (y + i) % Options::chunkSize;

				if (chunkY < 0 || chunkY >= Options::chunkColumnHeigth)
					continue;
				GetChunk(chunkY).SetBlock(x + j, blockY, z + k, BlockId::Leaf);
			}
		}
	}
}
