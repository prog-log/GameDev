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
	setupTransform(renderer);

	auto pDeviceContext = renderer.GetDeviceContext();
	size_t strides[1] = { sizeof(Vertex) };
	size_t offsets[1] = { 0 };
	pDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, strides, offsets);
	pDeviceContext->Draw(VERTEX_NUM, 0);
}

void Triangle::setupTransform(Renderer& renderer)
{
	// WorldMatrixを定数バッファに設定

	auto mtx = DirectX::XMMatrixTranslation(0.5f, 0.5f, 0);
	//auto mtx = DirectX::XMMatrixRotationZ(3.14f / 4.f);
	auto& cb = renderer.GetRenderParam().Cb2DTransformSet;
	auto pDeviceContext = renderer.GetDeviceContext();
	DirectX::XMStoreFloat4x4(&cb.Data.Transform, XMMatrixTranspose(mtx));
	//DirectX::XMStoreFloat4x4(&cb.Data.Transform, translate);
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// CBufferにひもづくハードウェアリソースマップ取得（ロックして取得）
	HRESULT hr = pDeviceContext->Map(
		cb.pBuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedResource);
	if (FAILED(hr)) {
		//DXTRACE_ERR(L"DrawSceneGraph failed", hr);
		return;
	}
	CopyMemory(mappedResource.pData, &cb.Data, sizeof(cb.Data));
	// マップ解除
	pDeviceContext->Unmap(cb.pBuffer, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &cb.pBuffer);
}

