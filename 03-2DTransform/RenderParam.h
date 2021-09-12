#pragma once
#include "ConstantBuffer.h"

struct RenderParam
{
	Cb2DTransformSet	Cb2DTransformSet;

	bool Initialize(Renderer& renderer);
	void Terminate(Renderer& renderer);

private:
	bool initConstantBuffer(Renderer& renderer);
};
