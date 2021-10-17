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
	void updateTransform();
	void setupTransform(Renderer& renderer);

private:
	float translateX_ = 0.f;
	float translateY_ = 0.f;
	float angle_ = 0.f;
	float scale_ = 1.f;
};
