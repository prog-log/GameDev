#include "Model.h"
#include "Mesh.h"
#include "Renderer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model()
{
}

Model::~Model()
{
	SAFE_DELETE_ARRAY(meshes_);
}

bool Model::Setup(Renderer& renderer, const char* filePath)
{
	// load処理
	Assimp::Importer importer;
	u_int flag = aiProcess_Triangulate;
	auto pScene = importer.ReadFile(filePath, flag);

	if (pScene == nullptr) {
		auto error =  importer.GetErrorString();
		return false;
	}

	meshNum_ = pScene->mNumMeshes;
	if (meshNum_ > 0) {
		meshes_ = new Mesh[meshNum_];
		for (u_int meshIdx = 0; meshIdx < pScene->mNumMeshes; ++meshIdx) {
			auto pMeshData = pScene->mMeshes[meshIdx];
			if (meshes_[meshIdx].Setup(renderer, pMeshData) == false) {
				return false;
			}
		}
	}

	return true;
}

void Model::Terminate()
{
	for (u_int meshIdx = 0; meshIdx < meshNum_; ++meshIdx) {
		meshes_[meshIdx].Terminate();
	}
	SAFE_DELETE_ARRAY(meshes_);
	meshNum_ = 0;
}

void Model::Draw(Renderer& renderer)
{
	setupTransform(renderer);

	for (u_int meshIdx = 0; meshIdx < meshNum_; ++meshIdx) {
		meshes_[meshIdx].Draw(renderer);
	}
}

void Model::setupTransform(Renderer& renderer)
{
	// WorldMatrixを定数バッファに設定

	auto& cb = renderer.GetRenderParam().CbTransformSet;

	//auto mtxS = XMMatrixScaling(scale_, scale_, 1.f);

	//auto mtxR = XMMatrixRotationX(angle_);
	//auto mtxR = XMMatrixRotationY(angle_);
	//auto mtxR = XMMatrixRotationZ(angle_);

	//auto mtxT = XMMatrixTranslation(translateX_, translateY_, 0);

	auto mtx = XMMatrixIdentity();

	// 左から変換が適用される
	//auto mtx = mtxT * mtxS;
	//auto mtx = mtxS * mtxT;

	//auto mtx = mtxT * mtxR;
	//auto mtx = mtxR * mtxT;

	XMStoreFloat4x4(&cb.Data.Transform, XMMatrixTranspose(mtx));
	//DirectX::XMStoreFloat4x4(&cb.Data.Transform, translate);
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	auto pDeviceContext = renderer.GetDeviceContext();
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

