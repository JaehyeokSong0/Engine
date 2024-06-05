#pragma once
#include "../Buffer/Buffer.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace Assimp;

class Mesh
{
public:
	Mesh(ID3D11Device* device, ID3D11DeviceContext* context, vector<Vertex>& vertices, vector<UINT>& indices);
	Mesh(const Mesh& mesh);
	~Mesh();

	void Render();

private:
	// DO NOT DEALLOCATE
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;

	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;

	UINT indexSize;

	bool isCopy;
};