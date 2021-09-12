#pragma once

struct Cb2DTransform
{
	DirectX::XMFLOAT4X4	Transform;
};

struct Cb2DTransformSet
{
	Cb2DTransform	Data;
	ID3D11Buffer*	pBuffer = nullptr;
};
