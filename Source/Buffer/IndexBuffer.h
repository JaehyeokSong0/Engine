#pragma once
#include "BaseBuffer.h"

class IndexBuffer : BaseBuffer
{
public:
	IndexBuffer() = default;
	~IndexBuffer() = default;

	HRESULT Create(ID3D11Device* device, const vector<UINT>& indices);
	void Bind(ID3D11DeviceContext* context);
};