#include "Chunk.h"
#include "World/World.h"
#include "ChunkMeshBuilder.h"
#include "Options/Options.h"

//Construtor
Chunk::Chunk(World& world, ChunkColumn& chunkColumn, int x, int y, int z)
	: m_world(world), m_chunkColumn(chunkColumn)
{
	m_position = { x , y, z };
	m_chunkData.fill(BlockId::Air);
	m_hasMesh = false;
}

//Destrutor
Chunk::~Chunk()
{
}

//Retorna a Mesh da chunk
ChunkMesh& Chunk::GetMesh()
{
	return m_mesh;
}

//Retorna a posição da chunk
glm::vec3 Chunk::GetLocation() const
{
	return m_position;
}

//Retorna o bloco dado uma posição
const BlockId Chunk::GetBlock(int x, int y, int z) const
{
	//Caso esteja fora da chunk acessa o bloco pela posição global
	if (OutOfBounds(x) || OutOfBounds(y) || OutOfBounds(z))
		return m_chunkColumn.GetBlock(GetChunkBlockPosition(x, y, z));

	return m_chunkData[GetIndex(x, y, z)];
}

//Retorna o bloco dado uma posição
const BlockId Chunk::GetBlock(const glm::ivec3& position) const
{
	return GetBlock(position.x, position.y, position.z);
}

std::array<BlockId, Options::chunkVolume>& Chunk::GetData()
{
	return m_chunkData;
}

//Verifica se a chunk já possui uma mesh construida
const bool Chunk::HasMesh() const
{
	return m_hasMesh;
}

//Muda o bloco na posição(x, y, z) da chunk, e marca que a mesh precisa ser reconstruida
void Chunk::SetBlock(int x, int y, int z, BlockId block)
{
	if (OutOfBounds(x) || OutOfBounds(y) || OutOfBounds(z))
		return m_chunkColumn.SetBlock(GetChunkBlockPosition(x, y, z), block);

	m_hasMesh = false;
	m_chunkData[GetIndex(x, y, z)] = block;
}

//Constroi a mesh da chunk
void Chunk::BuildMesh()
{
	//Classe auxiliar para criar a mesh
	ChunkMeshBuilder builder;
	builder.BuildMesh(*this);
	m_mesh.BufferMesh();
	m_hasMesh = true;
}

//Verifica se a coordenada value esta dentro dos limites da chunk
const bool Chunk::OutOfBounds(int value) const
{
	return value < 0 || value >= Options::chunkSize;
}

//retorna o index do array de BlockId's de acordo com x, y e z
const int Chunk::GetIndex(int x, int y, int z) const
{
	return x + y * Options::chunkSize + z * Options::chunkArea;
}

//retorna a posicao do bloco em coordenadas globais
const glm::ivec3 Chunk::GetGlobalPosition(int x, int y, int z) const
{
	return glm::ivec3(m_position.x * Options::chunkSize + x,
					 m_position.y * Options::chunkSize + y,
					 m_position.z * Options::chunkSize + z);
}

const glm::ivec3 Chunk::GetChunkBlockPosition(int x, int y, int z) const
{
	return glm::ivec3(x, m_position.y * Options::chunkSize + y, z);
}
