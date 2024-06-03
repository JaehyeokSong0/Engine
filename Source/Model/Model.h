#pragma once
#include "../Buffer/Buffer.h"
#include "../Component/Component.h"
#include "../Texture/Texture.h"

class Model : Component
{
public:
	Model(const ComponentClass& type = ComponentClass::MODEL);
	~Model();

	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* context);
	void Update() override;
	void Destroy() override;

	void UpdateMatrices(XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	// void SetPath(texturePath, modelPath) (TODO)
private:
	// Device and context are resources of the Renderer class, so DO NOT DELETE
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;

	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;

	Texture* texture = nullptr;

	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;
};
