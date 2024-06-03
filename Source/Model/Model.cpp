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

// �ؾ��ϴ� �� 
// : vb, ib, cb�� ��ü ���� �� render���� bind -> device, context �ʿ�
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
