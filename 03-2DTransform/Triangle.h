#pragma once

struct Triangle
{
	static constexpr size_t VERTEX_NUM = 3;
	Vertex	 Vertices[VERTEX_NUM];
	ID3D11Buffer* VertexBuffer = nullptr;

	Triangle();
	~Triangle();
	bool CreateVertexBuffer(Renderer& renderer);
	void DestroyVertexBuffer();
	void Draw(Renderer& renderer);

private:
	void setupTransform(Renderer& renderer);
};
