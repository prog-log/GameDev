#include "Triangle.h"
#include "Renderer.h"

Triangle::Triangle()
{
	Vertices[0] = { 0.f, 0.5f, 0.f };
	Vertices[1] = { 0.5f, -0.5f, 0.f };
	Vertices[2] = { -0.5f, -0.5f, 0.f };
}

Triangle::~Triangle()
{
	DestroyVertexBuffer();
}

bool Triangle::CreateVertexBuffer(Renderer& renderer)
{
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA vertexSubData;
	vertexSubData.pSysMem = Vertices;

	auto hr = renderer.GetDevice()->CreateBuffer(
		&vertexBufferDesc,
		&vertexSubData,
		&VertexBuffer
	);

	if (FAILED(hr)) return false;

	return true;
}

void Triangle::DestroyVertexBuffer()
{
	DX_SAFE_RELEASE(VertexBuffer);
}

void Triangle::Draw(Renderer& renderer)
{
	auto pDeviceContext = renderer.GetDeviceContext();
	size_t strides[1] = { sizeof(Vertex) };
	size_t offsets[1] = { 0 };
	pDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, strides, offsets);
	pDeviceContext->Draw(VERTEX_NUM, 0);
}

