#pragma once

struct Shader
{
	Shader() {}
	~Shader() {}

	void Terminate() {
		DX_SAFE_RELEASE(pVertexShader);
		DX_SAFE_RELEASE(pPixelShader);
		DX_SAFE_RELEASE(pInputLayout);
	}

	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11InputLayout* pInputLayout = nullptr;
};
