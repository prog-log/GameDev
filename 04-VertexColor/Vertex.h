﻿#pragma once

struct Vertex
{
	DirectX::XMFLOAT3 Position = {};
	DirectX::XMFLOAT4 Color = {};

	Vertex() {}
	Vertex(float x, float y, float z) {
		Position.x = x;
		Position.y = y;
		Position.z = z;
	}
};

