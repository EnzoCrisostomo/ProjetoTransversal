#pragma once
#include "Math/Vectors.h"
#include <vector>
#include <cinttypes>

typedef float GLfloat;

enum class BlockId : uint8_t
{
	Air = 0,
	GrassBlock,
	Dirt,
	Stone,
	Sand,
	SnowGrass,
	Snow,
	StoneBrick,
	Water,
	Lava,
	DarkWood,
	LightWood,
	PineWood,
	Leaf,
	LightLeaf,
	PineLeaf,
	Cactus,
	Mushroom,
	MushroomStalk,
	DarkPlanks,
	LightPlanks,
	PinePlanks,
	Bricks,
	Glass,
	BookShelf,
	Grass,
	Poppy,
	Lily,
	Dandelion,
	BlueOrchid,

	blockCount
};

enum class Transparency : uint8_t
{
	Opaque,
	Half,
	Full,
};

class Block
{
public:
	Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const bool isVegetation,
		const uint8_t topTextureIndex, const uint8_t sideTextureIndex, const uint8_t bottomTextureIndex);
	Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const bool isVegetation, 
		const uint8_t textureIndex);

	const bool operator == (const Block& other) const
	{
		return this->m_blockId == other.m_blockId;
	}
	const bool IsSolid() const { return m_isSolid; };
	const bool IsVegetation() const { return m_isVegetation; };

	Transparency IsTranslucent() const { return m_transparency; };

	const char* GetName() const { return m_name; };
	const BlockId& GetId() const { return m_blockId; };

	const uint8_t& GetTopTexture() const;
	const uint8_t& GetSideTexture() const;
	const uint8_t& GetBottomTexture() const;

private:
	uint8_t m_topTextureIndex;
	uint8_t m_sideTextureIndex;
	uint8_t m_bottomTextureIndex;

	const char* m_name;
	const BlockId m_blockId;
	const bool m_isSolid;
	const bool m_isVegetation;
	Transparency m_transparency;
};