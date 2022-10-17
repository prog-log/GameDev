#include "Camera.h"


Camera::Camera()
	: eyePos_(0, 0, -5)
	, focutPos_(0, 0, 0)
{
}

Camera::~Camera()
{

}

void Camera::Update()
{
	//eyePos_.x += 0.0001f;
	//if (eyePos_.x > 5.f) {
	//	eyePos_.x = -5.f;
	//}

	eyePos_.y += 0.03f;
	if (eyePos_.y > 10.f) {
		eyePos_.y = 0.f;
	}

	//eyePos_.z -= 0.0001f;
	//if (eyePos_.z < -10.f) {
	//	eyePos_.z = -5.f;
	//}
}

/*
 *	View変換行列取得
 */
DirectX::XMMATRIX Camera::GetViewMatrix() const
{
	// ビュー変換行列を求める
	XMMATRIX viewMat = XMMatrixLookAtLH(
		XMLoadFloat3(&eyePos_), XMLoadFloat3(&focutPos_), XMLoadFloat3(&up_));
	return viewMat;
}
