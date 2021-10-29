#pragma once

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#define DX_SAFE_RELEASE(x)	{ if(x) { (x)->Release(); (x)=NULL; } }

class Renderer
{
public:
	Renderer();
	~Renderer();
	
	bool Initialize(HWND hWindow);

	void Terminate();

	void Draw();

	void Swap();

	ID3D11Device* GetDevice() { return pD3DDevice_; }
	ID3D11DeviceContext* GetDeviceContext() { return pImmediateContext_; }

private:
	bool initDeviceAndSwapChain(HWND hWindow);
	bool initBackBuffer();

private:
	//! 機能レベルの配列
	static const UINT	FEATURE_LEVELS_NUM = 4;
	D3D_FEATURE_LEVEL	pFeatureLevels_[FEATURE_LEVELS_NUM] = {};
	//! デバイス作成時に返される機能レベル
	D3D_FEATURE_LEVEL	featureLevelsSupported_;

	//! デバイス
	ID3D11Device*			pD3DDevice_ = nullptr;
	//! デバイスコンテキスト
	ID3D11DeviceContext*	pImmediateContext_ = nullptr;
	//! スワップ・チェイン
	IDXGISwapChain*			pSwapChain_ = nullptr;

	//! 描画ターゲット・ビュー
	ID3D11RenderTargetView*	pRenderTargetView_ = nullptr;
	//! ビューポート
	D3D11_VIEWPORT			viewPort_[1];

	UINT	backBufferNum_ = 3;
	UINT	screenWidth_ = 0;
	UINT	screenHeight_ = 0;

};
