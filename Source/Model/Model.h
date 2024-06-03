#pragma once
#include "../Buffer/Buffer.h"
#include "../Component/Component.h"

const wstring TYPE_MODEL = L"Model";

class Model : Component
{
public:
	Model(const wstring type = TYPE_MODEL);
	~Model();

	HRESULT Initialize(ID3D11Device* device);
	void Update() override;
	void Destroy() override;

private:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;

	XMMATRIX worldMatrix;
};
