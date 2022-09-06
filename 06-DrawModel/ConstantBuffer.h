#pragma once

/*
 *	ワールド変換コンスタントバッファ
 */
struct CbTransform
{
	XMFLOAT4X4	Transform;
};

struct CbTransformSet
{
	CbTransform	Data;
	ID3D11Buffer*	pBuffer = nullptr;
};

/*
 *	View変換用コンスタントバッファ
 */
struct CbView
{
	XMFLOAT4X4	View;
};

struct CbViewSet
{
	CbView	Data;
	ID3D11Buffer*	pBuffer = nullptr;
};

/*
 *	投影行列用コンスタントバッファ
 */
struct CbProjection
{
	XMFLOAT4X4	Projection;
};

struct CbProjectionSet
{
	CbProjection	Data;
	ID3D11Buffer*	pBuffer = nullptr;
};
