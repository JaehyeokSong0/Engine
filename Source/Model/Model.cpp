#include <stdafx.h>
#include "Model.h"

Model::Model(const ComponentClass& type)
	: vertexBuffer(new VertexBuffer())
	, indexBuffer(new IndexBuffer())
	, constantBuffer(new ConstantBuffer())
	, texture(new Texture())
	, worldMatrix(XMMatrixIdentity())
	, viewMatrix(XMMatrixIdentity())
	, projectionMatrix(XMMatrixIdentity())
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

HRESULT Model::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	HRESULT hr = S_OK;

	this->device = device;
	this->context = context;

	// TEST CODE
	vector<Vertex> testVertex =
	{
		Vertex(XMFLOAT3(-0.5f, -0.5f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
		Vertex(XMFLOAT3(-0.5f, 0.5f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
		Vertex(XMFLOAT3(0.5f, 0.5f, 1.0f), XMFLOAT2(1.0f, 0.0f)),
		Vertex(XMFLOAT3(0.5f, -0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f))
	};
	vector<UINT> testIndex =
	{
		0, 1, 2,
		0, 2, 3
	};
	hr = texture->Initialize(device, context, L"Resources/Textures/cheems.png");
	if (FAILED(hr))
	{
		DebugLog("Texture initialization Failed");
		return hr;
	}

	hr = vertexBuffer->Create(device, testVertex);
	if (FAILED(hr))
	{
		DebugLog("Create Vertex buffer Failed");
		return hr;
	}

	hr = indexBuffer->Create(device, testIndex);
	if (FAILED(hr))
	{
		DebugLog("Create Index buffer Failed");
		return hr;
	}

	hr = constantBuffer->Create(device, sizeof(TransformCB));
	if (FAILED(hr))
	{
		DebugLog("Create Constant buffer Failed");
		return hr;
	}

	return hr;
}

void Model::Update()
{
	// Update constant buffer
	// DirectX use row-major matrix, otherwise HLSL use coloum-major matrix -> Transpose
	TransformCB transformCB = {};
	transformCB.worldMatrix = XMMatrixIdentity();
	transformCB.viewMatrix = XMMatrixTranspose(viewMatrix);
	transformCB.projectionMatrix = XMMatrixTranspose(projectionMatrix);
	constantBuffer->SetData(context, &transformCB, sizeof(transformCB));
	constantBuffer->Bind(context, 0u);

	context->PSSetShaderResources(0u, 1u, &texture->GetTextureRV());

	vertexBuffer->Bind(context);
	indexBuffer->Bind(context);

	context->DrawIndexed(6u, 0u, 0);

	// Bind texture, VB, IB, CB
	return;
}

void Model::Destroy()
{
	return;
}

void Model::UpdateMatrices(XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	this->viewMatrix = viewMatrix;
	this->projectionMatrix = projectionMatrix;
}
