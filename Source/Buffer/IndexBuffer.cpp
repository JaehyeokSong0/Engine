#include <stdafx.h>
#include "IndexBuffer.h"

HRESULT IndexBuffer::Create(ID3D11Device* device, const vector<UINT>& indices)
{
	HRESULT hr = S_OK;

	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = sizeof(UINT) * static_cast<UINT>(indices.size());
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0u;

	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = indices.data();

	hr = device->CreateBuffer(&bufferDesc, &initData, buffer.GetAddressOf());

	return hr;
}

void IndexBuffer::Bind(ID3D11DeviceContext* context)
{
	context->IASetIndexBuffer(buffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
}
