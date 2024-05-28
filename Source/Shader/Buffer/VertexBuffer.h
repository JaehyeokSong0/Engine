#pragma once
#include "BaseBuffer.h"

class VertexBuffer : BaseBuffer
{
public:
	VertexBuffer() = default;
	~VertexBuffer() = default;
	
	HRESULT Create(ID3D11Device* device,const vector<Vertex>& vertices);
	void Bind(ID3D11DeviceContext* context);
};