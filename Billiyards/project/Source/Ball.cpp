#include "Ball.h"
#include "Screen.h"

Ball::Ball(int num, VECTOR3 pos)
{
	hImage = LoadGraph("data/textures/billiyard.png");
	number = num;
	position = pos;
	velocity = VECTOR3(1, -0.5f, 0) * 10;
	catched = false;
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (catched)
	{
		// 左ボタンを離したので
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0)
		{
			int x, y;
			GetMousePoint(&x, &y);
			velocity = VECTOR3(catchX - x, catchY - y, 0) / 20.0f;
			catched = false;
		}
	}
	else
	{
		if (GetMouseInput() & MOUSE_INPUT_LEFT)
		{
			// 左クリックしたときの座標を取っておく
			catched = true;
			GetMousePoint(&catchX, &catchY);
		}
	}

	// 反射
	position += velocity;
	if (position.y >= Screen::HEIGHT - 28)
	{
		velocity.y *= -1;
	}
	if (position.y < 0 + 28)
	{
		velocity.y *= -1;
	}
	if (position.x >= Screen::WIDTH - 28)
	{
		velocity.x *= -1;
	}
	if (position.x < 0 + 28)
	{
		velocity.x *= -1;
	}
	// 毎フレーム一定量減らす
	 // ベクトルの長さを求める
	 // 長さを一定値減らす
	 // 長さが0以下になれば、velocityは(0,0,0)
	 // velocityを、その長さに書き換える←velocityの長さを1にしてから、長さを掛ける
	
	float len = velocity.Size(); // ベクトルの長さを求める
	len -= 0.01f;
	if (len <= 0)
	{
		velocity = VECTOR3(0, 0, 0);
	}
	else
	{
		VECTOR3 n = velocity.Normalize(); // ベクトルの長さを1にする 
		                                  // nは向きを求めている
		velocity = n * len;
	}
}

void Ball::Draw()
{
	int x = (number - 1) % 4;
	int y = (number - 1) / 4;
	DrawRectGraph(position.x - 32, position.y - 32, x * 64, y * 64, 64, 64, hImage, TRUE);
}
