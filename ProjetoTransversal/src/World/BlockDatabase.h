#pragma once
#include "Block.h"
#include <vector>
class BlockDatabase
{
public:
	BlockDatabase();

	const Block& GetBlockInfo(const BlockId& blockId) const;
private:
	std::vector<Block> m_blockData;
};

