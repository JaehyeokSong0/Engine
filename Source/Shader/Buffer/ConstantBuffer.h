#pragma once
#include "BaseBuffer.h"

class ConstantBuffer : BaseBuffer
{
public:
	ConstantBuffer() = default;
	~ConstantBuffer() = default;

	HRESULT Create(ID3D11Device* device, UINT size);
	HRESULT SetData(ID3D11DeviceContext* context, void* data);
	void Bind(ID3D11DeviceContext* context);

private:
	D3D11_MAPPED_SUBRESOURCE mapInitData = {}; // context->Map() 호출 위해 필요한 subresource
};