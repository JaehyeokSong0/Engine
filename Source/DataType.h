#pragma once
#include <stdafx.h>

struct Vertex
{
	Vertex(float x, float y, float z, float u, float v)
		: position(x, y, z), texCoord(u, v)
	{}

	Vertex(XMFLOAT3 pos, XMFLOAT2 tex)
		: position(pos), texCoord(tex)
	{}

	XMFLOAT3 position;
	XMFLOAT2 texCoord;
};

struct Constant_Buffer
{
	// TEST Variables
	float xOffset = 0;
	float yOffset = 0;
};