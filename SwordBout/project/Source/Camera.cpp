#include "Camera.h"

namespace {
	static float distance = 500.0f; // �L��������̋���
	static float lookHeight = 200.0f; // �����_�̍���
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
	if (GetMousePoint(&mouseX, &mouseY)); // �}�E�X�̈ʒu
	int moveX = mouseX - prevMouseX; // �}�E�X�ړ���
	int moveY = mouseY - prevMouseY;

	// �J������]����
	transform.rotation.y += moveX * 0.2f * DegToRad;
	transform.rotation.x += moveY * 0.1f * DegToRad;
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	// �J������]����
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
