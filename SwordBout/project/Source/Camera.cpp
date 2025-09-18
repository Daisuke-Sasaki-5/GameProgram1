#include "Camera.h"
#include "PadInput.h"

namespace {
	static float distance = 500.0f; // キャラからの距離
	static float lookHeight = 200.0f; // 注視点の高さ
};

Camera::Camera()
{
	GetMousePoint(&prevMouseX, &prevMouseY);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	PadInput* pad = FindGameObject<PadInput>();
	float padX = pad->RStickX();
	transform.rotation.y += padX * 3.0f * DegToRad;
	float padY = pad->RStickY();
	transform.rotation.x += padY * 2.0f * DegToRad;

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		transform.rotation.y += 3.0f * DegToRad;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		transform.rotation.y -= 3.0f * DegToRad;
	}

	if (CheckHitKey(KEY_INPUT_UP))
	{
		transform.rotation.x += 2.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		transform.rotation.x -= 2.0f * DegToRad;
	}

	int mouseX, mouseY;
	if (GetMousePoint(&mouseX, &mouseY)); // マウスの位置
	int moveX = mouseX - prevMouseX; // マウス移動量
	int moveY = mouseY - prevMouseY;

	// カメラ回転操作
	transform.rotation.y += moveX * 0.2f * DegToRad;
	transform.rotation.x += moveY * 0.1f * DegToRad;
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	// カメラ回転制限
	if (transform.rotation.x >= 85.0f * DegToRad)
	{
		transform.rotation.x = 85.0f * DegToRad;
	}
	if (transform.rotation.x <= -45.0f * DegToRad)
	{
		transform.rotation.x = -45.0f * DegToRad;
	}

	VECTOR3 camPos = lookPosition + VECTOR3(0, 150, 0)  + VECTOR3(0, 0, -427) * MGetRotX(transform.rotation.x) * MGetRotY(transform.rotation.y);
	VECTOR3 lookPos = lookPosition + VECTOR3(0, 200, 0);
	SetCameraPositionAndTarget_UpVecY(camPos, lookPos);
}

void Camera::Draw()
{
}

void Camera::SetPlayerPosition(const VECTOR& pos)
{
	lookPosition = pos;
}
