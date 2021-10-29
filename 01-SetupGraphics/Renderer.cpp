#include "Renderer.h"

Renderer::Renderer()
{
	pFeatureLevels_[0] = D3D_FEATURE_LEVEL_11_1;
	pFeatureLevels_[1] = D3D_FEATURE_LEVEL_11_0;
	pFeatureLevels_[2] = D3D_FEATURE_LEVEL_10_1;
	pFeatureLevels_[3] = D3D_FEATURE_LEVEL_10_0;
}

Renderer::~Renderer()
{

}

bool Renderer::Initialize(HWND hWindow)
{
	// Windowに合わせてスクリーンサイズ初期化
	RECT rc;
	GetClientRect(hWindow, &rc);
	screenWidth_ = rc.right - rc.left;
	screenHeight_ = rc.bottom - rc.top;

	initDeviceAndSwapChain(hWindow);

	initBackBuffer();

	return true;
}

void Renderer::Terminate()
{
	// デバイス・ステートのクリア
	if (pImmediateContext_) pImmediateContext_->ClearState();

	// スワップ チェインをウインドウ モードにする
	if (pSwapChain_) pSwapChain_->SetFullscreenState(FALSE, NULL);

	// 取得したインターフェイスの開放
	DX_SAFE_RELEASE(pRenderTargetView_);
	DX_SAFE_RELEASE(pSwapChain_);

	DX_SAFE_RELEASE(pImmediateContext_);
	DX_SAFE_RELEASE(pD3DDevice_);
}

void Renderer::Draw()
{
	if (!pImmediateContext_ || !pRenderTargetView_) return;

	float color[] = { 0.f, 0.f, 1.f, 0.f };
	pImmediateContext_->ClearRenderTargetView(pRenderTargetView_, color);
}

void Renderer::Swap()
{
	// バックバッファの表示（画面をすぐに更新）
	HRESULT hr = pSwapChain_->Present(0, 0);
	if (FAILED(hr)) {
		//TRACE("Swap failed(%0x08x)\n", hr);
		return;
	}
}

bool Renderer::initDeviceAndSwapChain(HWND hWindow)
{
	// デバイスとスワップ・チェイン作成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = backBufferNum_;		// バックバッファの数
	sd.BufferDesc.Width = screenWidth_;	// バックバッファの幅
	sd.BufferDesc.Height = screenHeight_;	// バックバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// フォーマット
	sd.BufferDesc.RefreshRate.Numerator = 60;	// リフレッシュレート（分母）
	sd.BufferDesc.RefreshRate.Denominator = 1;	// リフレッシュレート（分子）
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バックバッファの使用法
	sd.OutputWindow = hWindow;		// 関連付けるウィンドウ
	sd.SampleDesc.Count = 1;			// マルチサンプル（アンチエイリアス）の数
	sd.SampleDesc.Quality = 0;			// マルチサンプル（アンチエイリアス）のクオリティ
	sd.Windowed = TRUE;		// ウィンドウモード（TRUEがウィンドウモード）
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// モード自動切り替え

#if defined(DEBUG) || defined(_DEBUG)
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT createDeviceFlags = 0;
#endif

	const D3D_DRIVER_TYPE DriverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	HRESULT hr;
	for (auto type : DriverTypes) {
		// ハードウェアデバイスを作成
		hr = D3D11CreateDeviceAndSwapChain(
			NULL, type, NULL, createDeviceFlags,
			pFeatureLevels_, FEATURE_LEVELS_NUM, D3D11_SDK_VERSION, &sd,
			&pSwapChain_, &pD3DDevice_, &featureLevelsSupported_, &pImmediateContext_);
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) return false;

	return true;
}

bool Renderer::initBackBuffer()
{
	HRESULT hr;

	// スワップ・チェインから最初のバック・バッファを取得する
	ID3D11Texture2D *pBackBuffer;  // バッファのアクセスに使うインターフェイス
	hr = pSwapChain_->GetBuffer(
		0,                         // バック・バッファの番号
		__uuidof(ID3D11Texture2D), // バッファにアクセスするインターフェイス
		(LPVOID*)&pBackBuffer);    // バッファを受け取る変数
	if (FAILED(hr)) {
		//TRACE("InitBackBuffer g_pSwapChain->GetBuffer(%0x08x)\n", hr);  // 失敗
		return false;
	}

	// バック・バッファの情報
	D3D11_TEXTURE2D_DESC descBackBuffer;
	pBackBuffer->GetDesc(&descBackBuffer);

	// バック・バッファの描画ターゲット・ビューを作る
	hr = pD3DDevice_->CreateRenderTargetView(
		pBackBuffer,           // ビューでアクセスするリソース
		NULL,                  // 描画ターゲット・ビューの定義
		&pRenderTargetView_); // 描画ターゲット・ビューを受け取る変数
	DX_SAFE_RELEASE(pBackBuffer);  // 以降、バック・バッファは直接使わないので解放
	if (FAILED(hr)) {
		//TRACE("InitBackBuffer g_pD3DDevice->CreateRenderTargetView(%0x08x)\n", hr);  // 失敗
		return false;
	}

	// ビューポートの設定
	viewPort_[0].TopLeftX = 0.0f;    // ビューポート領域の左上X座標。
	viewPort_[0].TopLeftY = 0.0f;    // ビューポート領域の左上Y座標。
	viewPort_[0].Width    = static_cast<float>(screenWidth_);  // ビューポート領域の幅
	viewPort_[0].Height   = static_cast<float>(screenHeight_);  // ビューポート領域の高さ
	viewPort_[0].MinDepth = 0.0f; // ビューポート領域の深度値の最小値
	viewPort_[0].MaxDepth = 1.0f; // ビューポート領域の深度値の最大値
	pImmediateContext_->RSSetViewports(1, &viewPort_[0]);

	return true;
}

