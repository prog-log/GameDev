#pragma once

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
#define DX_SAFE_RELEASE(x)	{ if(x) { (x)->Release(); (x)=NULL; } }
#include "Vertex.h"

using namespace DirectX;
class Renderer;
