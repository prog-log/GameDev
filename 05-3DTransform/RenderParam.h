#pragma once
#include "ConstantBuffer.h"

/*
 *	描画パラメータ
 *	コンスタントバッファの値などを保持
 */
struct RenderParam
{
	CbTransformSet	CbTransformSet;
	CbViewSet		CbViewSet;
	CbProjectionSet	CbProjectionSet;

	bool Initialize(Renderer& renderer);
	void Terminate(Renderer& renderer);

private:
	bool initConstantBuffer(Renderer& renderer);
};
