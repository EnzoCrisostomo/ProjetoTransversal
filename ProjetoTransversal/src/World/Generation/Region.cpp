#include "Region.h"
#include "Options/Options.h"
#include <cinttypes>
#include "World/Block/Block.h"

Region::Region(VectorXZ pos)
	:	m_position(pos)
{
	m_file = new std::fstream(Options::worldRegionsPath + "region" + std::to_string(pos.x) + "_" + std::to_string(pos.z) + ".bin",
		std::ios_base::in | std::ios_base::out | std::ios_base::binary);

	if (!m_file->is_open())
	{
		delete m_file;
		m_file = new std::fstream(Options::worldRegionsPath + "region" + std::to_string(pos.x) + "_" + std::to_string(pos.z) + ".bin",
			std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

		uint64_t temp = 0ULL;
		m_file->write(reinterpret_cast<char*>(&temp), sizeof(uint64_t));
	}
}

Region::~Region()
{
	delete m_file;
}