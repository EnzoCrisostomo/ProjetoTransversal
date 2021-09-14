#include "BlockDatabase.h"
#include <fstream>
#include <string>
#include <iostream>
#include <exception>

BlockDatabase::BlockDatabase()
{
	//cria um bloco para cada Id de bloco
	m_blockData.emplace_back(BlockId::Air, false, true, glm::vec2(0, 0));
	m_blockData.emplace_back(BlockId::Grass, true, false, glm::vec2(0.25, 0.5), glm::vec2(0, 0.5), glm::vec2(0.75, 0.75));
	m_blockData.emplace_back(BlockId::Dirt, true, false, glm::vec2(0.75, 0.75));
	m_blockData.emplace_back(BlockId::Stone, true, false, glm::vec2(0.5, 0.75));
	m_blockData.emplace_back(BlockId::Sand, true, false, glm::vec2(0.5, 0.5));
	m_blockData.emplace_back(BlockId::Wood, true, false, glm::vec2(0.75, 0.25), glm::vec2(0.5, 0.25), glm::vec2(0.75, 0.25));
	m_blockData.emplace_back(BlockId::Leaf, true, false, glm::vec2(0.25, 0.0));
}

const Block& BlockDatabase::GetBlockInfo(const BlockId& blockId) const
{
	//retorna as informacoes do bloco de acordo com o id de bloco passado
	return m_blockData[(int)blockId];
}
