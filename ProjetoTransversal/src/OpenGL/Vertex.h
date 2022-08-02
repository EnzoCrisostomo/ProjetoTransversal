#pragma once

struct Vertex
{
	struct
	{
		float x;
		float y;
		float z;
	}positions;

	struct
	{
		float u;
		float v;
	}textureCoords;

	struct
	{
		float r;
		float g;
		float b;
		float a;
	}color;
};