// Base class of VB, IB, CB
#pragma once
#include <stdafx.h>

class BaseBuffer 
{
public:
	ID3D11Buffer* GetBuffer() const
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* GetAddress() const
	{
		return buffer.GetAddressOf();
	}

protected:
	BaseBuffer() = default;
	virtual ~BaseBuffer() = default;

	ComPtr<ID3D11Buffer> buffer;
	D3D11_BUFFER_DESC bufferDesc = {};
	D3D11_SUBRESOURCE_DATA initData = {};

};