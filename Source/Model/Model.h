#pragma once
#include "../Component/Component.h"
#include "../Texture/Texture.h"
#include "../Mesh/Mesh.h"

class Model : Component
{
public:
	Model(const ComponentClass& type = ComponentClass::MODEL);
	~Model();

	// use string& for filePath to use Assimp::Importer.LoadFile()
	HRESULT Initialize(const string& filePath, ID3D11Device* device, ID3D11DeviceContext* context);
	virtual void Start() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void UpdateMatrices(XMMATRIX viewMatrix, XMMATRIX projectionMatrix);

	HRESULT LoadModel(const string& filePath);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* node, const aiScene* scene);
	// void SetPath(texturePath, modelPath) (TODO)
private:
	// Device and context are resources of the Renderer class, so DO NOT DELETE
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;

	ConstantBuffer* constantBuffer = nullptr;

	Texture* texture = nullptr;

	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	vector<Mesh> meshes;
};
