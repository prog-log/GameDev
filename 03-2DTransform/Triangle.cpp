#include "Triangle.h"
#include "Renderer.h"

Triangle::Triangle()
{
	//Vertices[0] = { 0.f, 0.5f, 0.f };
	//Vertices[1] = { 0.5f, -0.5f, 0.f };
	//Vertices[2] = { -0.5f, -0.5f, 0.f };

	// ��3
	auto sqrt3 = sqrtf(3);
	Vertices[0] = { 0.f, sqrt3 / 3.f, 0.f };
	Vertices[1] = { 0.5f, -sqrt3 / 6.f, 0.f };
	Vertices[2] = { -0.5f, -sqrt3 / 6.f, 0.f };
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
	updateTransform();

	setupTransform(renderer);

	auto pDeviceContext = renderer.GetDeviceContext();
	size_t strides[1] = { sizeof(Vertex) };
	size_t offsets[1] = { 0 };
	pDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, strides, offsets);
	pDeviceContext->Draw(VERTEX_NUM, 0);
}

void Triangle::updateTransform()
{
	// ���s�ړ�
	//translateX_ += 0.0001f;
	//if (translateX_ >= 1.f) translateX_ = -1.f;
	//translateY_ += 0.0001f;
	//if (translateY_ >= 1.f) translateY_ = -1.f;
	translateX_ = 0.5f;

	// ��]
	//angle_ += XM_PI / 60000.f;
	angle_ = XM_PI / 2.f;

	// �X�P�[��
	//scale_ += 0.0001f;
	//if (scale_ >= 2.0f) scale_ = 0.5f;
	scale_ = 2.f;
}

void Triangle::setupTransform(Renderer& renderer)
{
	// WorldMatrix��萔�o�b�t�@�ɐݒ�

	auto& cb = renderer.GetRenderParam().CbTransformSet;

	auto mtxS = XMMatrixScaling(scale_, scale_, 1.f);

	//auto mtxR = XMMatrixRotationX(angle_);
	//auto mtxR = XMMatrixRotationY(angle_);
	auto mtxR = XMMatrixRotationZ(angle_);

	auto mtxT = XMMatrixTranslation(translateX_, translateY_, 0);

	//auto mtx = XMMatrixIdentity();

	// ������ϊ����K�p�����
	//auto mtx = mtxT * mtxS;
	//auto mtx = mtxS * mtxT;

	//auto mtx = mtxT * mtxR;
	auto mtx = mtxR * mtxT;

	XMStoreFloat4x4(&cb.Data.Transform, XMMatrixTranspose(mtx));
	//DirectX::XMStoreFloat4x4(&cb.Data.Transform, translate);
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	auto pDeviceContext = renderer.GetDeviceContext();
	// CBuffer�ɂЂ��Â��n�[�h�E�F�A���\�[�X�}�b�v�擾�i���b�N���Ď擾�j
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
	// �}�b�v����
	pDeviceContext->Unmap(cb.pBuffer, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &cb.pBuffer);
}

