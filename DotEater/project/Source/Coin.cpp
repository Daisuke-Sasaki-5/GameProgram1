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
		homingUpdate();
#if false
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
#endif
	}
	else {
		float diff = VSize(pPos - position);
		if (diff < 120.0f) // コインに当たってる
		{
			gotten = true;
			homingStart();
		}
	}
}

void Coin::homingStart()
{
	Player* pl = FindGameObject<Player>();
	VECTOR pPos = pl->GetPositin(); // プレイヤーの足元の座標
	pPos += VGet(0, 50, 0); // コインと同じ高さにする
	VECTOR v = pPos - position;
	velocity = VNorm(v) * -10.0f; // 向き×移動速度
}

void Coin::homingUpdate()
{
	position += velocity;

	Player* pl = FindGameObject<Player>();
	VECTOR pPos = pl->GetPositin(); // プレイヤーの足元の座標
	pPos += VGet(0, 50, 0); // コインと同じ高さにする
	VECTOR v = pPos - position; // 相手へのベクトル
	if (VSize(v) < 20.0f)
	{
		DestroyMe();

	}

	VECTOR a = VNorm(velocity); // 自分の正面
	VECTOR b = VNorm(v); // 相手へのベクトルの向き
	float co = VDot(a, b); // これがcosθ
	float speed = (co + 1.0f) * 10.0f; // θが0だと速く、θが大きいと遅く
	                       // coはθが1～-1になるので、1のときに20、-1のときに0
	float len = VSize(velocity); // 今の長さ
	if (len > speed) // 早すぎ
	{
		len -= 0.1f;
	}
	else // 遅すぎ
	{
		len += 0.05f;
	}
	velocity = VNorm(velocity) * len;

	VECTOR rightVec = velocity * MGetRotY(90.0 * DegToRad); // 右ベクトル
	float ip = VDot(rightVec, v); // 内積を求める
	// 速ければ角度を小さく、遅ければ角度を大きく
	float rspeed = (25.0f - len) / 5.0f;
	if (ip > 0) // 右にいる
	{
		
		velocity = velocity * MGetRotY(rspeed * DegToRad); // 右旋回
	}
	else
	{
		velocity = velocity * MGetRotY(-rspeed * DegToRad); // 左旋回
	}
}
