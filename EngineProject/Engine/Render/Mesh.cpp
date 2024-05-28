#include <PreCompiledHeader.h>
#include "Mesh.h"
#include "../Engine/Engine.h"

namespace DemoEngine
{
	Mesh::Mesh(void* vertexData, unsigned int vertexCount, void* indexData, unsigned int indexCount)
		: vertexData(vertexData), vertexCount(vertexCount), indexData(indexData), indexCount(indexCount)
	{
		auto device = g_Engine->Device();

		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(float) * 3 * vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexBufferData = {};
		vertexBufferData.pSysMem = vertexData;

		ThrowIfFailed(
			device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer), 
			TEXT("Failed to create vertex buffer"));

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc .Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc .ByteWidth = sizeof(unsigned int) * indexCount;
		indexBufferDesc .BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexBufferData = {};
		indexBufferData.pSysMem = indexData;

		ThrowIfFailed(
			device->CreateBuffer(&indexBufferDesc, &indexBufferData, &indexBuffer),
			TEXT("Failed to create index buffer"));
	}

	Mesh::~Mesh()
	{
		SafeRelease(vertexBuffer);
		SafeRelease(indexBuffer);
	}

	void Mesh::Bind()
	{
		auto context = g_Engine->Context();

		unsigned int stride = sizeof(float) * 3;
		unsigned int offset = 0u;
		context->IASetVertexBuffers(0u, 1u, &vertexBuffer, &stride, &offset);
		context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0u);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}