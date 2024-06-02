#include <stdafx.h>
#include "Model.h"

Model::Model()
	: vertexBuffer(new VertexBuffer())
	, indexBuffer(new IndexBuffer())
	, constantBuffer(new ConstantBuffer())
	, worldMatrix(XMMatrixIdentity())
{
}

Model::~Model()
{
	if (vertexBuffer != nullptr)
	{
		delete vertexBuffer;
		vertexBuffer = nullptr;
	}
	if (indexBuffer!= nullptr)
	{
		delete indexBuffer;
		indexBuffer= nullptr;
	}
	if (constantBuffer!= nullptr)
	{
		delete constantBuffer;
		constantBuffer = nullptr;
	}
}

// 해야하는 것 
// : vb, ib, cb로 물체 생성 후 render에서 bind -> device, context 필요
HRESULT Model::Initialize()
{
	HRESULT hr = S_OK;

	return hr;
}

HRESULT Model::Render()
{
	HRESULT hr = S_OK;

	return hr;
}
