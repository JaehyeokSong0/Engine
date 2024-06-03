#include <stdafx.h>
#include "ConstantBuffer.h"

HRESULT ConstantBuffer::Create(ID3D11Device* device, UINT size)
{
	HRESULT hr = S_OK;

	if (size % 16 != 0)
		size = ((size / 16) + 1) * 16;

	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = size;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = device->CreateBuffer(&bufferDesc, nullptr, buffer.GetAddressOf());

	return hr;
}

HRESULT ConstantBuffer::SetData(ID3D11DeviceContext* context, void* data, UINT size)
{
	HRESULT hr = S_OK;

	ZeroMemory(&mapInitData, sizeof(mapInitData));
	hr = context->Map(
		buffer.Get(), 
		0u, // Subresource index
		D3D11_MAP_WRITE_DISCARD, // 쓰기용 매핑 & 기존 리소스 discard
		0u, // gpu 사용 중일 때 cpu 작업 지정 플래그
		&mapInitData
	);
	if (FAILED(hr))
		return hr;

	// (dest, source, length)
	CopyMemory(mapInitData.pData, data, size);

	context->Unmap(buffer.Get(), 0);
	return hr;
}

void ConstantBuffer::Bind(ID3D11DeviceContext* context, UINT slot)
{
	context->VSSetConstantBuffers(slot, 1u, buffer.GetAddressOf());
}