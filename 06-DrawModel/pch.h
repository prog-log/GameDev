#pragma once

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
#define DX_SAFE_RELEASE(x)	{ if(x) { (x)->Release(); (x)=nullptr; } }
#define SAFE_DELETE(p)    { if(p) { delete p; p = nullptr; }}
#define SAFE_DELETE_ARRAY(p)    { if(p) { delete[] p; p = nullptr; }}
#include "Vertex.h"

using namespace DirectX;
class Renderer;
