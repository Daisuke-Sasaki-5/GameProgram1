#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	int speed = 2; // プレイヤーの速さ
	int hImage;
	VECTOR2 position;
	float velocity;
	bool prevJumpKey; // 前のジャンプキー
	bool onGround; // 地面にいる

	bool goaled; // ゴール
};

// インスタンスはメンバー変数と関数を持っているものの実体
// 変数は値を保持するもの
