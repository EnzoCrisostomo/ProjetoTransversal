#include "ChunkColumn.h"
#include "World/World.h"
#include "Options/Options.h"
#include "World/Generation/NoiseGenerator.h"
#include "World/Generation/WorldGen.h"
#include <math.h>
#include <random>
#include <fstream>

ChunkColumn::ChunkColumn(World& world, VectorXZ position, std::vector<std::pair<glm::ivec3, BlockId>> blocksToSet )
	: m_world(world), m_position(position)
{
	m_chunks.reserve(Options::chunkColumnHeigth);
	for (int y = 0; y < Options::chunkColumnHeigth; y++)
		m_chunks.emplace_back(m_world, *this, m_position.x, y, m_position.z);

	if (m_position == VectorXZ{ 0, 0 })
	{
		std::ifstream* myFile = new std::ifstream("data.bin", std::ios::in | std::ios::binary);
		if (myFile->is_open())
		{
			for (auto& chunk : m_chunks)
			{
				auto& data = chunk.GetData();
				myFile->read(reinterpret_cast<char*>(data.data()), sizeof(BlockId) * Options::chunkVolume);
				myFile->seekg(myFile->tellg() + static_cast<std::streampos>(sizeof(BlockId) * Options::chunkVolume));
			}
			return;
		}
		myFile->close();
		delete myFile;
	}
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
		int heigthXZ = chunkDataMap[x * Options::chunkSize + z].height;
		BlockId surfaceBlock = chunkDataMap[x * Options::chunkSize + z].blockId;

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
			/*if (x == 0 || z == 0 || x == 15 || z == 15)
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
			/*if (x == 0 || z == 0 || x == 15 || z == 15)
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
	if (m_position == VectorXZ{0, 0})
	{
		std::ofstream* myFile = new std::ofstream("data.bin", std::ios::out | std::ios::binary);
		if (myFile->is_open())
		{
			for (auto& chunk : m_chunks)
			{
				auto& data = chunk.GetData();
				myFile->write(reinterpret_cast<char*>(data.data()), sizeof(BlockId) * Options::chunkVolume);
				myFile->seekp(myFile->tellp() + static_cast<std::streampos>(sizeof(BlockId) * Options::chunkVolume));
			}
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
