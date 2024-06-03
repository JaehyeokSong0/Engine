#include <stdafx.h>
#include "Model.h"

Model::Model(const wstring type)
	: vertexBuffer(new VertexBuffer())
	, indexBuffer(new IndexBuffer())
	, constantBuffer(new ConstantBuffer())
	, worldMatrix(XMMatrixIdentity())
{
	this->type = type;
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
HRESULT Model::Initialize(ID3D11Device* device)
{
	HRESULT hr = S_OK;

	return hr;
}

void Model::Update()
{

	return;
}

void Model::Destroy()
{
	return;
}
