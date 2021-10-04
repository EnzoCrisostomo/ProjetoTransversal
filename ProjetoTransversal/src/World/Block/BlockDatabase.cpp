#include "BlockDatabase.h"
#include <fstream>
#include <string>
#include <iostream>
#include <exception>

BlockDatabase::BlockDatabase()
{
	//cria um bloco para cada Id de bloco
	//						 nome			, id					, solido, translucido			, index da textura no atlas
	m_blockData.emplace_back("Air"			, BlockId::Air			, false	, Transparency::Full	, 0);
	m_blockData.emplace_back("Grass"		, BlockId::Grass		, true	, Transparency::Opaque	, 1, 0, 2);
	m_blockData.emplace_back("Dirt"			, BlockId::Dirt			, true	, Transparency::Opaque	, 2);
	m_blockData.emplace_back("Stone"		, BlockId::Stone		, true	, Transparency::Opaque	, 3);
	m_blockData.emplace_back("Sand"			, BlockId::Sand			, true	, Transparency::Opaque	, 4);
	m_blockData.emplace_back("SnowGrass"	, BlockId::SnowGrass	, true	, Transparency::Opaque	, 6, 5, 2);
	m_blockData.emplace_back("Snow"			, BlockId::Snow			, true	, Transparency::Opaque	, 6);
	m_blockData.emplace_back("StoneBrick"	, BlockId::StoneBrick	, true	, Transparency::Opaque	, 7);
	m_blockData.emplace_back("Water"		, BlockId::Water		, false	, Transparency::Full	, 8);
	m_blockData.emplace_back("Lava"			, BlockId::Lava			, false	, Transparency::Full	, 9);
	m_blockData.emplace_back("DarkWood"		, BlockId::DarkWood		, true	, Transparency::Opaque	, 11, 10, 11);
	m_blockData.emplace_back("LightWood"	, BlockId::LightWood	, true	, Transparency::Opaque	, 13, 12, 13);
	m_blockData.emplace_back("PineWood"		, BlockId::PineWood		, true	, Transparency::Opaque	, 15, 14, 15);
	m_blockData.emplace_back("Leaf"			, BlockId::Leaf			, true	, Transparency::Half	, 16);
	m_blockData.emplace_back("LightLeaf"	, BlockId::LightLeaf	, true	, Transparency::Half	, 17);
	m_blockData.emplace_back("PineLeaf"		, BlockId::PineLeaf		, true	, Transparency::Half	, 18);
	m_blockData.emplace_back("Cactus"		, BlockId::Cactus		, true	, Transparency::Half	, 19, 20, 19);
	m_blockData.emplace_back("Mushroom"		, BlockId::Mushroom		, true	, Transparency::Opaque	, 21);
	m_blockData.emplace_back("MushroomStalk", BlockId::MushroomStalk, true	, Transparency::Opaque	, 23);
	m_blockData.emplace_back("DarkPlanks"	, BlockId::DarkPlanks	, true	, Transparency::Opaque	, 24);
	m_blockData.emplace_back("LightPlanks"	, BlockId::LightPlanks	, true	, Transparency::Opaque	, 25);
	m_blockData.emplace_back("PinePlanks"	, BlockId::PinePlanks	, true	, Transparency::Opaque	, 26);
	m_blockData.emplace_back("Bricks"		, BlockId::Bricks		, true	, Transparency::Opaque	, 27);
	m_blockData.emplace_back("Glass"		, BlockId::Glass		, true	, Transparency::Full	, 28);
	m_blockData.emplace_back("BookShelf"	, BlockId::BookShelf	, true	, Transparency::Opaque	, 26, 29, 26);
}

const Block& BlockDatabase::GetBlockInfo(const BlockId& blockId) const
{
	//retorna as informacoes do bloco de acordo com o id de bloco passado
	for (auto& bloco : m_blockData)
		if (bloco.GetId() == blockId)
			return bloco;

	std::cerr << "!!! Bloco não encontrado !!!\n";
	throw std::runtime_error("!!! Bloco não encontrado !!!");
	return m_blockData[(int)blockId];
}
