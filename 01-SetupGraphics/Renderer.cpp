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
	// Window�ɍ��킹�ăX�N���[���T�C�Y������
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
	// �f�o�C�X�E�X�e�[�g�̃N���A
	if (pImmediateContext_) pImmediateContext_->ClearState();

	// �X���b�v �`�F�C�����E�C���h�E ���[�h�ɂ���
	if (pSwapChain_) pSwapChain_->SetFullscreenState(FALSE, NULL);

	// �擾�����C���^�[�t�F�C�X�̊J��
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
	// �o�b�N�o�b�t�@�̕\���i��ʂ������ɍX�V�j
	HRESULT hr = pSwapChain_->Present(0, 0);
	if (FAILED(hr)) {
		//TRACE("Swap failed(%0x08x)\n", hr);
		return;
	}
}

bool Renderer::initDeviceAndSwapChain(HWND hWindow)
{
	// �f�o�C�X�ƃX���b�v�E�`�F�C���쐬
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = backBufferNum_;		// �o�b�N�o�b�t�@�̐�
	sd.BufferDesc.Width = screenWidth_;	// �o�b�N�o�b�t�@�̕�
	sd.BufferDesc.Height = screenHeight_;	// �o�b�N�o�b�t�@�̍���
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// �t�H�[�}�b�g
	sd.BufferDesc.RefreshRate.Numerator = 60;	// ���t���b�V�����[�g�i����j
	sd.BufferDesc.RefreshRate.Denominator = 1;	// ���t���b�V�����[�g�i���q�j
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// �o�b�N�o�b�t�@�̎g�p�@
	sd.OutputWindow = hWindow;		// �֘A�t����E�B���h�E
	sd.SampleDesc.Count = 1;			// �}���`�T���v���i�A���`�G�C���A�X�j�̐�
	sd.SampleDesc.Quality = 0;			// �}���`�T���v���i�A���`�G�C���A�X�j�̃N�I���e�B
	sd.Windowed = TRUE;		// �E�B���h�E���[�h�iTRUE���E�B���h�E���[�h�j
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// ���[�h�����؂�ւ�

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
		// �n�[�h�E�F�A�f�o�C�X���쐬
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

	// �X���b�v�E�`�F�C������ŏ��̃o�b�N�E�o�b�t�@���擾����
	ID3D11Texture2D *pBackBuffer;  // �o�b�t�@�̃A�N�Z�X�Ɏg���C���^�[�t�F�C�X
	hr = pSwapChain_->GetBuffer(
		0,                         // �o�b�N�E�o�b�t�@�̔ԍ�
		__uuidof(ID3D11Texture2D), // �o�b�t�@�ɃA�N�Z�X����C���^�[�t�F�C�X
		(LPVOID*)&pBackBuffer);    // �o�b�t�@���󂯎��ϐ�
	if (FAILED(hr)) {
		//TRACE("InitBackBuffer g_pSwapChain->GetBuffer(%0x08x)\n", hr);  // ���s
		return false;
	}

	// �o�b�N�E�o�b�t�@�̏��
	D3D11_TEXTURE2D_DESC descBackBuffer;
	pBackBuffer->GetDesc(&descBackBuffer);

	// �o�b�N�E�o�b�t�@�̕`��^�[�Q�b�g�E�r���[�����
	hr = pD3DDevice_->CreateRenderTargetView(
		pBackBuffer,           // �r���[�ŃA�N�Z�X���郊�\�[�X
		NULL,                  // �`��^�[�Q�b�g�E�r���[�̒�`
		&pRenderTargetView_); // �`��^�[�Q�b�g�E�r���[���󂯎��ϐ�
	DX_SAFE_RELEASE(pBackBuffer);  // �ȍ~�A�o�b�N�E�o�b�t�@�͒��ڎg��Ȃ��̂ŉ��
	if (FAILED(hr)) {
		//TRACE("InitBackBuffer g_pD3DDevice->CreateRenderTargetView(%0x08x)\n", hr);  // ���s
		return false;
	}

	// �r���[�|�[�g�̐ݒ�
	viewPort_[0].TopLeftX = 0.0f;    // �r���[�|�[�g�̈�̍���X���W�B
	viewPort_[0].TopLeftY = 0.0f;    // �r���[�|�[�g�̈�̍���Y���W�B
	viewPort_[0].Width    = static_cast<float>(screenWidth_);  // �r���[�|�[�g�̈�̕�
	viewPort_[0].Height   = static_cast<float>(screenHeight_);  // �r���[�|�[�g�̈�̍���
	viewPort_[0].MinDepth = 0.0f; // �r���[�|�[�g�̈�̐[�x�l�̍ŏ��l
	viewPort_[0].MaxDepth = 1.0f; // �r���[�|�[�g�̈�̐[�x�l�̍ő�l
	pImmediateContext_->RSSetViewports(1, &viewPort_[0]);

	return true;
}

