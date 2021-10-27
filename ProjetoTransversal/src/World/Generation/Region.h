#pragma once
#include "Math/VectorXZ.h"
#include <fstream>

struct Region
{
	Region(VectorXZ pos);

	~Region();

	std::fstream* file;
	VectorXZ position;
};
