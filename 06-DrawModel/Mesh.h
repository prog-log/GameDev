#pragma once
struct aiMesh;

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Setup(Renderer& renderer, aiMesh* pMeshData);
	void Terminate();
	void Draw(Renderer& renderer);

private:
	bool createVertexBuffer(Renderer& renderer);
	bool createIndexBuffer(Renderer& renderer);
	void destroyVertexBuffer();
	void destroyIndexBuffer();

private:
	// データの解釈ワーク
	Vertex*		vertices_ = nullptr;
	u_int*		indices_ = nullptr;
	u_int		vertexNum_ = 0;
	u_int		indexNum_ = 0;

	// バッファリソース
	ID3D11Buffer* vertexBuffer_ = nullptr;
	ID3D11Buffer* indexBuffer_ = nullptr;
};
