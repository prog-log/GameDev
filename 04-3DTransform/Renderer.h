#pragma once
#include "Shader.h"
#include "Triangle.h"
#include "RenderParam.h"

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
	RenderParam& GetRenderParam() { return renderParam_; }

	bool CompileShader(const WCHAR* vsPath, const WCHAR* psPath, Shader& outShader);

private:
	bool initDeviceAndSwapChain(HWND hWindow);
	bool initBackBuffer();

private:
	//! �@�\���x���̔z��
	static const UINT	FEATURE_LEVELS_NUM = 4;
	D3D_FEATURE_LEVEL	pFeatureLevels_[FEATURE_LEVELS_NUM] = {};
	//! �f�o�C�X�쐬���ɕԂ����@�\���x��
	D3D_FEATURE_LEVEL	featureLevelsSupported_;

	//! �f�o�C�X
	ID3D11Device*			pD3DDevice_ = nullptr;
	//! �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext*	pImmediateContext_ = nullptr;
	//! �X���b�v�E�`�F�C��
	IDXGISwapChain*			pSwapChain_ = nullptr;

	//! �`��^�[�Q�b�g�E�r���[
	ID3D11RenderTargetView*	pRenderTargetView_ = nullptr;
	//! �r���[�|�[�g
	D3D11_VIEWPORT			viewPort_[1];

	UINT	backBufferNum_ = 3;
	UINT	screenWidth_ = 0;
	UINT	screenHeight_ = 0;

	Shader		defaultShader_;
	Triangle	sampleTriangle_;

	RenderParam	renderParam_;
};
