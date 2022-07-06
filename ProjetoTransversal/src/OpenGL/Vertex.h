#pragma once
#include <cinttypes>

struct Vertex
{
	struct
	{
		uint8_t x;
		uint8_t y;
		uint8_t z;
	}positions;

	uint8_t light;
	uint8_t textureIndex;
};