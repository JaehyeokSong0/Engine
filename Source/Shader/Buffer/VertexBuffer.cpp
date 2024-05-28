#include <stdafx.h>
#include "VertexBuffer.h"

HRESULT VertexBuffer::Create(ID3D11Device* device, const vector<Vertex>& vertices)
{
	HRESULT hr = S_OK;

	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = sizeof(Vertex) * static_cast<UINT>(vertices.size());
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0u; // 0 : NO CPU Access

	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertices.data(); // pSysMem : 초기화 데이터 (const void*)

	hr = device->CreateBuffer(&bufferDesc, &initData, buffer.GetAddressOf());

	return hr; // hr 디버깅은 호출 함수에서 확인
}

void VertexBuffer::Bind(ID3D11DeviceContext* context)
{
	UINT offset = 0;
	UINT stride = sizeof(Vertex);

	context->IASetVertexBuffers(0u, 1u, buffer.GetAddressOf(), &stride, &offset);
}
