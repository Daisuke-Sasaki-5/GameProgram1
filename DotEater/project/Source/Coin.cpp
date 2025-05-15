#include "Coin.h"
#include "Player.h"

Coin::Coin(VECTOR pos)
{
	hModel = MV1LoadModel("data/models/Coin.mv1");
	position = pos;
	gotten = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	Player* pl = FindGameObject<Player>();
	VECTOR pPos = pl->GetPositin(); // プレイヤーの足元の座標
	pPos += VGet(0, 50, 0); // コインと同じ高さにする

	if(gotten)
	{
		// 取られたので、プレイヤーに近づく
		// 1.コインからプレイヤーに向かうベクトルを作る
		VECTOR v = pPos - position;
		// 2.そのベクトルの長さが5のものを作る
		v = VNorm(v) * 5.0f; // VNorm()はベクトルの長さを1にする関数
		// 3.コインの座標に加える
		position += v;
		// 4.コインとプレイヤーの距離が10以下になったらDestoryMe()
		float diff = VSize(pPos - position);
		if (diff < 10.0f) // コインに当たってる
		{
			DestroyMe();
		}
	}
	else {
		float diff = VSize(pPos - position);
		if (diff < 120.0f) // コインに当たってる
		{
			gotten = true;
		}
	}
}
