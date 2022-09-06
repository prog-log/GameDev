#pragma once

class Camera
{
public:
	Camera();
	~Camera();

	void Update();

	XMMATRIX GetViewMatrix() const;

private:
	XMFLOAT3	eyePos_ = { 0, 0, 0};
	XMFLOAT3	focutPos_ = { 0, 0, 0 };
	XMFLOAT3	up_ = { 0, 1.f, 0 };
};
