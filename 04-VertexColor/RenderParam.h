#pragma once
#include "ConstantBuffer.h"

struct RenderParam
{
	CbTransformSet	CbTransformSet;

	bool Initialize(Renderer& renderer);
	void Terminate(Renderer& renderer);

private:
	bool initConstantBuffer(Renderer& renderer);
};
