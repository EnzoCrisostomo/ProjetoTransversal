#include "BlockDatabase.h"
#include <fstream>
#include <string>
#include <iostream>
#include <exception>

BlockDatabase::BlockDatabase()
{
	//cria um bloco para cada Id de bloco
	//						ID(nome), solido, translúcido, posição da textura no atlas
	m_blockData.emplace_back(BlockId::Air, false, true, glm::vec2(0.00, 0.00));
	m_blockData.emplace_back(BlockId::Grass, true, false, glm::vec2(0.25, 0.75), glm::vec2(0, 0.75), glm::vec2(0.50, 0.75));
	m_blockData.emplace_back(BlockId::Dirt, true, false, glm::vec2(0.50, 0.75));
	m_blockData.emplace_back(BlockId::Stone, true, false, glm::vec2(0.75, 0.75));
	m_blockData.emplace_back(BlockId::DarkWood, true, false, glm::vec2(0.25, 0.50), glm::vec2(0.00, 0.50), glm::vec2(0.25, 0.50));
	m_blockData.emplace_back(BlockId::LightWood, true, false, glm::vec2(0.75, 0.50), glm::vec2(0.5, 0.50), glm::vec2(0.75, 0.50));
	m_blockData.emplace_back(BlockId::Leaf, true, false, glm::vec2(0.00, 0.25));
	m_blockData.emplace_back(BlockId::Sand, true, false, glm::vec2(0.25, 0.25));
	m_blockData.emplace_back(BlockId::SandStone, true, false, glm::vec2(0.50, 0.25), glm::vec2(0.75, 0.25), glm::vec2(0.50, 0.25));
	m_blockData.emplace_back(BlockId::StoneBrick, true, false, glm::vec2(0.00, 0.00));
	m_blockData.emplace_back(BlockId::DarkPlanks, true, false, glm::vec2(0.25, 0.00));
	m_blockData.emplace_back(BlockId::LightPlanks, true, false, glm::vec2(0.50, 0.00));
	m_blockData.emplace_back(BlockId::Lava, true, false, glm::vec2(0.75, 0.00));
}

const Block& BlockDatabase::GetBlockInfo(const BlockId& blockId) const
{
	//retorna as informacoes do bloco de acordo com o id de bloco passado
	return m_blockData[(int)blockId];
}
