#pragma once
#include<DirectXMath.h>

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

struct TransformCB
{
	XMMATRIX worldMatrix; // object -> world
	XMMATRIX viewMatrix; // world -> camera
	XMMATRIX projectionMatrix; // camera -> clip
};