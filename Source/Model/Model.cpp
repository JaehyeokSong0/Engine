#include <stdafx.h>
#include "Model.h"

Model::Model(const ComponentClass& type)
	: constantBuffer(new ConstantBuffer())
	, texture(new Texture())
	, worldMatrix(XMMatrixIdentity())
	, viewMatrix(XMMatrixIdentity())
	, projectionMatrix(XMMatrixIdentity())
{
	this->type = type;
}

Model::~Model()
{
	meshes.clear();
	if (constantBuffer!= nullptr)
	{
		delete constantBuffer;
		constantBuffer = nullptr;
	}
	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
}

HRESULT Model::Initialize(const string& filePath, ID3D11Device* device, ID3D11DeviceContext* context)
{
	HRESULT hr = S_OK;

	this->device = device;
	this->context = context;


	hr = this->LoadModel(filePath);
	if (FAILED(hr))
	{
		DebugLog("LoadModel Failed");
		return hr;
	}

	hr = texture->Initialize(device, context, L"Resources/Textures/cheems.png");
	//hr = texture->Initialize(device, context, L"Resources/Models/RubiksCube.mtl");
	if (FAILED(hr))
	{
		DebugLog("Texture initialization Failed");
		return hr;
	}

	hr = constantBuffer->Create(device, sizeof(TransformCB));
	if (FAILED(hr))
	{
		DebugLog("Create Constant buffer Failed");
		return hr;
	}

	return hr;
}

void Model::Start()
{
}

void Model::Update()
{
	// Update constant buffer
	// DirectX use row-major matrix, otherwise HLSL use coloum-major matrix -> Transpose
	TransformCB transformCB = {};
	transformCB.worldMatrix = XMMatrixIdentity();
	transformCB.viewMatrix = XMMatrixTranspose(viewMatrix);
	transformCB.projectionMatrix = XMMatrixTranspose(projectionMatrix);
	constantBuffer->SetData(context, &transformCB, sizeof(transformCB));
	constantBuffer->Bind(context, 0u);
	context->PSSetSamplers(0u, 1u, &texture->GetSamplerState()); // PixelShader.hlsl에서 register에 매핑
	context->PSSetShaderResources(0u, 1u, &texture->GetTextureRV());
	
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].Render();

	// Bind texture, VB, IB, CB
	return;
}

void Model::Destroy()
{
	delete this;
}

void Model::UpdateMatrices(XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	this->viewMatrix = viewMatrix;
	this->projectionMatrix = projectionMatrix;
}

HRESULT Model::LoadModel(const string& filePath)
{
	HRESULT hr = S_OK;

	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile
	(
		filePath,
		aiProcess_Triangulate
		| aiProcess_ConvertToLeftHanded
	);

	if (pScene == nullptr)
		return E_FAIL;

	meshes.reserve(pScene->mNumMeshes);
	this->ProcessNode(pScene->mRootNode, pScene);

	return hr;
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.emplace_back(this->ProcessMesh(mesh, scene)); // Avoid calling copy constructor with using meshes.reserve()
		// meshes.push_back(this->ProcessMesh(mesh, scene)); // Calls Mesh(const Mesh& mesh) here
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
	
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<UINT> indices;
	vector<Texture> textures;

	// Vertices
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		XMFLOAT3 position = XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		XMFLOAT2 texture = XMFLOAT2(0.0f, 0.0f);

		if (mesh->mTextureCoords[0])
			texture = XMFLOAT2((float)mesh->mTextureCoords[0][i].x, (float)mesh->mTextureCoords[0][i].y);

		vertices.push_back(Vertex(position, texture));
	}

	// Indices
	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Textures
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> // TODO
	}

	return Mesh(device, context, vertices, indices);
}