#include <stdafx.h>
#include "Mesh.h"

Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* context, 
	vector<Vertex>& vertices, vector<UINT>& indices, vector<Texture>& textures)
	: device(device)
	, context(context)
	, vertexBuffer(new VertexBuffer())
	, indexBuffer(new IndexBuffer())
	, textures(textures)
	, indexSize(0u)
	, isCopy(false)
{
	HRESULT hr = S_OK;
	
	hr = vertexBuffer->Create(device, vertices);
	if (FAILED(hr))
		DebugLog("Create Vertex buffer Failed");

	hr = indexBuffer->Create(device, indices);
	if (FAILED(hr))
		DebugLog("Create Index buffer Failed");

	indexSize = static_cast<UINT>(indices.size());
}

Mesh::Mesh(const Mesh& mesh)
	: device(mesh.device)
	, context(mesh.context)
	, vertexBuffer(mesh.vertexBuffer)
	, indexBuffer(mesh.indexBuffer)
	, indexSize(mesh.indexSize)
	, isCopy(true)
{}

Mesh::~Mesh()
{
	if (isCopy == true)
	{
		if (vertexBuffer != nullptr)
		{
			delete vertexBuffer;
			vertexBuffer = nullptr;
		}
		if (indexBuffer != nullptr)
		{
			delete indexBuffer;
			indexBuffer = nullptr;
		}
	}
}


void Mesh::Render()
{
	vertexBuffer->Bind(context);
	indexBuffer->Bind(context);

	context->DrawIndexed(indexSize, 0u, 0);
}
