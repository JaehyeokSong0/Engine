// Included in <stdafx.h>
#pragma once
#include<DirectXMath.h>
using namespace DirectX;

const XMFLOAT3 XMFLOAT3_ZERO = XMFLOAT3(0.0f, 0.0f, 0.0f);
const XMVECTOR XMVECTOR_ZERO = { 0.0f, 0.0f, 0.0f };

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

struct Transform
{
	XMFLOAT3 position;
	XMFLOAT3 rotation;
};

struct TransformCB
{
	XMMATRIX worldMatrix; // object -> world
	XMMATRIX viewMatrix; // world -> camera
	XMMATRIX projectionMatrix; // camera -> clip
};