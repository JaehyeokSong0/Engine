#pragma once

namespace DemoEngine
{
	class Mesh
	{
	public:
		Mesh(void* vertexData, unsigned int vertexCount, void* indexData, unsigned int indexCount);
		~Mesh();

		void Bind();

		unsigned int VertexCount() const { return vertexCount; }
		unsigned int IndexCount() const { return indexCount; }

	private:
		struct ID3D11Buffer* vertexBuffer = nullptr;
		void* vertexData = nullptr;
		unsigned int vertexCount = 0u;

		struct ID3D11Buffer* indexBuffer = nullptr;
		void* indexData = nullptr;
		unsigned int indexCount = 0u;
	};
}
