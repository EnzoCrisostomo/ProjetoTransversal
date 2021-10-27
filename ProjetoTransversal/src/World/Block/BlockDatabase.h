#pragma once
#include "Block.h"
#include <vector>
class BlockDatabase
{
public:
	static BlockDatabase& Get()
	{
		static BlockDatabase instance;
		return instance;
	}
	const Block& GetBlockInfo(const BlockId& blockId) const;
private:
	BlockDatabase();
	std::vector<Block> m_blockData;
};

