#include "Region.h"
#include "Options/Options.h"
#include <cinttypes>
#include "World/Block/Block.h"

Region::Region(VectorXZ pos)
	:	position(pos)
{
	file = new std::fstream(Options::worldRegionsPath + "region" + std::to_string(pos.x) + "_" + std::to_string(pos.z) + ".bin",
		std::ios_base::in | std::ios_base::out | std::ios_base::binary);

	if (!file->is_open())
	{
		delete file;
		file = new std::fstream(Options::worldRegionsPath + "region" + std::to_string(pos.x) + "_" + std::to_string(pos.z) + ".bin",
			std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

		uint64_t temp = 0ULL;
		file->write(reinterpret_cast<char*>(&temp), sizeof(uint64_t));
	}
}

Region::~Region()
{
	delete file;
}