#include "Mesh.h"
#include "Renderer.h"
#include <assimp/mesh.h>

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	Terminate();
}

bool Mesh::Setup(Renderer& renderer, aiMesh* pMeshData)
{
	// 頂点データ取得
	vertexNum_ = pMeshData->mNumVertices;
	vertices_ = new Vertex[vertexNum_];
	for (u_int vertexIdx = 0; vertexIdx < vertexNum_; ++vertexIdx) {
		auto& pos = pMeshData->mVertices[vertexIdx];
		vertices_[vertexIdx].Position = XMFLOAT3(pos.x, pos.y, pos.z);
		constexpr float COLOR = 0.5f;
		vertices_[vertexIdx].Color = XMFLOAT4(COLOR, COLOR, COLOR, 1.f);
	}
	if (createVertexBuffer(renderer) == false) {
		return false;
	}

	// 頂点インデックスデータ取得（TriangleList前提）
	indexNum_ = pMeshData->mNumFaces * 3;
	indices_ = new u_int[indexNum_];
	for (u_int faceIdx = 0; faceIdx < pMeshData->mNumFaces; ++faceIdx) {
		auto& face = pMeshData->mFaces[faceIdx];
		assert(face.mNumIndices == 3);
		for (u_int idx = 0; idx < 3; ++idx) {
			indices_[faceIdx * 3 + idx] = face.mIndices[idx];
		}
	}
	if (createIndexBuffer(renderer) == false) {
		return false;
	}

	return true;
}

void Mesh::Terminate()
{
	destroyVertexBuffer();
	destroyIndexBuffer();
	SAFE_DELETE_ARRAY(vertices_);
	vertexNum_ = 0;
	SAFE_DELETE_ARRAY(indices_);
	indexNum_ = 0;
}

bool Mesh::createVertexBuffer(Renderer& renderer)
{
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexNum_;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA vertexSubData;
	vertexSubData.pSysMem = vertices_;

	auto hr = renderer.GetDevice()->CreateBuffer(
		&vertexBufferDesc,
		&vertexSubData,
		&vertexBuffer_
	);

	if (FAILED(hr)) return false;

	return true;
}

bool Mesh::createIndexBuffer(Renderer& renderer)
{
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = indexNum_ * 4;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA indexSubData;
	indexSubData.pSysMem = indices_;

	auto hr = renderer.GetDevice()->CreateBuffer(
		&indexBufferDesc,
		&indexSubData,
		&indexBuffer_
	);

	if (FAILED(hr)) return false;

	return true;
}

void Mesh::destroyVertexBuffer()
{
	DX_SAFE_RELEASE(vertexBuffer_);
}

void Mesh::destroyIndexBuffer()
{
	DX_SAFE_RELEASE(indexBuffer_);
}

void Mesh::Draw(Renderer& renderer)
{
	//setupTransform(renderer);

	auto pDeviceContext = renderer.GetDeviceContext();
	UINT strides[1] = { sizeof(Vertex) };
	UINT offsets[1] = { 0 };
	pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer_, strides, offsets);
	pDeviceContext->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	pDeviceContext->DrawIndexed(indexNum_, 0, 0);
}

