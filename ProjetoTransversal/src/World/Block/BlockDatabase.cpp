#include "BlockDatabase.h"
#include <fstream>
#include <string>
#include <iostream>
#include <exception>

BlockDatabase::BlockDatabase()
{
	//cria um bloco para cada Id de bloco
	//						 nome			, id					, solido, translucido			, index da textura no atlas
	m_blockData.emplace_back("Air"			, BlockId::Air			, false, Transparency::Full  , false, 0);
	m_blockData.emplace_back("GrassBlock"	, BlockId::GrassBlock	, true , Transparency::Opaque, false, 1, 0, 2);
	m_blockData.emplace_back("Dirt"			, BlockId::Dirt			, true , Transparency::Opaque, false, 2);
	m_blockData.emplace_back("Stone"		, BlockId::Stone		, true , Transparency::Opaque, false, 3);
	m_blockData.emplace_back("Sand"			, BlockId::Sand			, true , Transparency::Opaque, false, 4);
	m_blockData.emplace_back("SnowGrass"	, BlockId::SnowGrass	, true , Transparency::Opaque, false, 6, 5, 2);
	m_blockData.emplace_back("Snow"			, BlockId::Snow			, true , Transparency::Opaque, false, 6);
	m_blockData.emplace_back("StoneBrick"	, BlockId::StoneBrick	, true , Transparency::Opaque, false, 7);
	m_blockData.emplace_back("Water"		, BlockId::Water		, false, Transparency::Full  , false, 8);
	m_blockData.emplace_back("Lava"			, BlockId::Lava			, false, Transparency::Full  , false, 9);
	m_blockData.emplace_back("DarkWood"		, BlockId::DarkWood		, true , Transparency::Opaque, false, 11, 10, 11);
	m_blockData.emplace_back("LightWood"	, BlockId::LightWood	, true , Transparency::Opaque, false, 13, 12, 13);
	m_blockData.emplace_back("PineWood"		, BlockId::PineWood		, true , Transparency::Opaque, false, 15, 14, 15);
	m_blockData.emplace_back("Leaf"			, BlockId::Leaf			, true , Transparency::Half  , false, 16);
	m_blockData.emplace_back("LightLeaf"	, BlockId::LightLeaf	, true , Transparency::Half  , false, 17);
	m_blockData.emplace_back("PineLeaf"		, BlockId::PineLeaf		, true , Transparency::Half  , false, 18);
	m_blockData.emplace_back("Cactus"		, BlockId::Cactus		, true , Transparency::Half  , false, 19, 20, 19);
	m_blockData.emplace_back("Mushroom"		, BlockId::Mushroom		, true , Transparency::Opaque, false, 21);
	m_blockData.emplace_back("MushroomStalk", BlockId::MushroomStalk, true , Transparency::Opaque, false, 23);
	m_blockData.emplace_back("DarkPlanks"	, BlockId::DarkPlanks	, true , Transparency::Opaque, false, 24);
	m_blockData.emplace_back("LightPlanks"	, BlockId::LightPlanks	, true , Transparency::Opaque, false, 25);
	m_blockData.emplace_back("PinePlanks"	, BlockId::PinePlanks	, true , Transparency::Opaque, false, 26);
	m_blockData.emplace_back("Bricks"		, BlockId::Bricks		, true , Transparency::Opaque, false, 27);
	m_blockData.emplace_back("Glass"		, BlockId::Glass		, true , Transparency::Full  , false, 28);
	m_blockData.emplace_back("BookShelf"	, BlockId::BookShelf	, true , Transparency::Half  , false, 26, 29, 26);
	m_blockData.emplace_back("Grass"		, BlockId::Grass		, false, Transparency::Half  , true , 30);
	m_blockData.emplace_back("Poppy"		, BlockId::Poppy		, false, Transparency::Half  , true , 31);
	m_blockData.emplace_back("Lily"			, BlockId::Lily			, false, Transparency::Half  , true , 32);
	m_blockData.emplace_back("Dandelion"	, BlockId::Dandelion	, false, Transparency::Half  , true , 33);
	m_blockData.emplace_back("BlueOrchid"	, BlockId::BlueOrchid	, false, Transparency::Half  , true , 34);
}

const Block& BlockDatabase::GetBlockInfo(const BlockId& blockId) const
{
	//retorna as informacoes do bloco de acordo com o id de bloco passado
	for (auto& bloco : m_blockData)
		if (bloco.GetId() == blockId)
			return bloco;

	std::cerr << "!!! Bloco " << static_cast<uint8_t>(blockId) << " nao encontrado !!!\n";
	//throw std::runtime_error("!!! Bloco não encontrado !!!");
	return m_blockData[0];
}