#include "ChunkMesh.h"
#include "Options/Options.h"
#include <iostream>

static constexpr uint8_t textureIndices[] = { 0, 1, 3, 2 };

namespace Face
{
	const std::vector<GLfloat> front
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
	};

	const std::vector<GLfloat> back
	{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
	};

	const std::vector<GLfloat> left
	{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,
	};

	const std::vector<GLfloat> right
	{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,
	};

	const std::vector<GLfloat> top
	{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,
	};

	const std::vector<GLfloat> bottom
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};

	const std::vector<GLfloat> diagonals =
	{
		0, 0, 1,
		1, 0, 0,
		1, 1, 0,
		0, 1, 1,

		1, 0, 1,
		0, 0, 0,
		0, 1, 0,
		1, 1, 1,
	};
}

ChunkMesh::~ChunkMesh()
{
}

//Adiciona os vertices de uma face para a mesh
void ChunkMesh::AddBlockFace(const std::vector<GLfloat>& blockFace,
							 const uint8_t& textureIndex,
							 const glm::ivec3& blockPosition)
{
	//Vertex Positions
	for (int i = 0, index = 0; i < 4; i++)
	{
		m_blocksMesh.vertices.push_back(MountVertex(blockFace, textureIndex, blockPosition, i, index));
	}
	//Indices
	m_blocksMesh.indices.insert(m_blocksMesh.indices.end(),
		{
			m_blocksIndicesCount,
			m_blocksIndicesCount + 1,
			m_blocksIndicesCount + 2,

			m_blocksIndicesCount + 2,
			m_blocksIndicesCount + 3,
			m_blocksIndicesCount
		});
	m_blocksIndicesCount += 4;
}

void ChunkMesh::AddWaterBlockFace(std::vector<GLfloat> blockFace,
							 const uint8_t& textureIndex,
							 const glm::ivec3& blockPosition,
							 const bool isUpper)
{
	//TODO refazer altura da agua no bloco de cima

	/*if(isUpper)
		for (int i = 1; i < 11; i+=3)
			blockFace[i] = blockFace[i] == 1 ? 0.8f : 0;*/

	//Vertex Positions
	for (int i = 0, index = 0; i < 4; i++)
	{
		m_waterMesh.vertices.push_back(MountVertex(blockFace, textureIndex, blockPosition, i, index));
	}
	
	//Indices
	m_waterMesh.indices.insert(m_waterMesh.indices.end(),
		{
			m_waterIndicesCount,
			m_waterIndicesCount + 1,
			m_waterIndicesCount + 2,

			m_waterIndicesCount + 2,
			m_waterIndicesCount + 3,
			m_waterIndicesCount
		});
	m_waterIndicesCount += 4;
}

void ChunkMesh::AddVegetationBlock(const uint8_t& textureIndex, const glm::ivec3& blockPosition)
{
	const std::vector<GLfloat>& blockFace = Face::diagonals;
	//Vertex Positions
	for (int i = 0, index = 0; i < 8; i++)
	{
		m_vegetationMesh.vertices.push_back(MountVertex(blockFace, textureIndex, blockPosition, i, index));
	}

	for (int i = 0; i < 2; i++)
	{
		//Indices
		m_vegetationMesh.indices.insert(m_vegetationMesh.indices.end(),
			{
				m_vegetationIndicesCount,
				m_vegetationIndicesCount + 1,
				m_vegetationIndicesCount + 2,

				m_vegetationIndicesCount + 2,
				m_vegetationIndicesCount + 3,
				m_vegetationIndicesCount
			});
		m_vegetationIndicesCount += 4;
	}
}

//Carrega a mesh para a placa de video
//Cria o Model da mesh
void ChunkMesh::BufferMesh()
{
	m_blocksModel.SetData(m_blocksMesh);
	m_blocksMesh.Free();
	m_blocksIndicesCount = 0;
	
	m_vegetationModel.SetData(m_vegetationMesh);
	m_vegetationMesh.Free();
	m_hasVegetation = m_vegetationIndicesCount > 0;
	m_vegetationIndicesCount = 0;
	
	m_waterModel.SetData(m_waterMesh);
	m_waterMesh.Free();
	m_hasWater = m_waterIndicesCount > 0;
	m_waterIndicesCount = 0;
}

const Model& ChunkMesh::GetVegetationModel() const
{
	return m_vegetationModel;
}
const Model& ChunkMesh::GetBlocksModel() const
{
	return m_blocksModel;
}
const Model& ChunkMesh::GetWaterModel() const
{
	return m_waterModel;
}

inline Vertex ChunkMesh::MountVertex(const std::vector<GLfloat> &blockFace, const uint8_t& textureIndex,
									 const glm::ivec3& blockPosition, int &i, int &index) const
{
	Vertex vertex;

	//positions
	vertex.positions.x = (int)blockFace[index] + blockPosition.x * 8;
	index++;
	vertex.positions.y = (int)blockFace[index] + blockPosition.y * 8;
	index++;
	vertex.positions.z = (int)blockFace[index] + blockPosition.z * 8;
	index++;

	//iluminação
	vertex.light = 3 * (blockFace == Face::top || blockFace == Face::diagonals)
		+ 2 * (blockFace == Face::left || blockFace == Face::right)
		+ 1 * (blockFace == Face::front || blockFace == Face::back)
		+ 0 * (blockFace == Face::bottom);

	//textura
	uint8_t value = textureIndex << 20;
	//Para determinar qual ponta do quad da textura
	value |= textureIndices[i%4] << 6;
	vertex.textureIndex = value;

	return vertex;
}
