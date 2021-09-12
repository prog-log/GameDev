#include "RenderParam.h"
#include "Renderer.h"

bool RenderParam::Initialize(Renderer& renderer)
{
    auto result = initConstantBuffer(renderer);
    if (result == false) return false;

    return true;
}

void RenderParam::Terminate(Renderer& renderer)
{
	DX_SAFE_RELEASE(Cb2DTransformSet.pBuffer);
}

bool RenderParam::initConstantBuffer(Renderer& renderer)
{
	// 定数バッファの定義
	D3D11_BUFFER_DESC cBufferDesc;
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.StructureByteStride = 0;

	// 定数バッファ①の作成
	cBufferDesc.ByteWidth = sizeof(Cb2DTransform);	// バッファ・サイズ
	auto hr = renderer.GetDevice()->CreateBuffer(&cBufferDesc, NULL, &Cb2DTransformSet.pBuffer);
	if (FAILED(hr)) {
		// DXTRACE_ERR(L"InitDirect3D g_pD3DDevice->CreateBuffer", hr);
		return false;
	}
	return true;
}
