#pragma once
#include "../Buffer/Buffer.h"

class Model
{
public:
	Model();
	~Model();

	HRESULT Initialize();
	HRESULT Render();

private:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;

	XMMATRIX worldMatrix;
};
