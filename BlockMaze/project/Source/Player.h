#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	int speed = 2; // �v���C���[�̑���
	int hImage;
	VECTOR2 position;
};