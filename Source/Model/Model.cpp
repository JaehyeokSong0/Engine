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

// �ؾ��ϴ� �� 
// : vb, ib, cb�� ��ü ���� �� render���� bind -> device, context �ʿ�
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
