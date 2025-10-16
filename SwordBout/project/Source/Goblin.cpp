#include "Goblin.h"
#include <assert.h>
#include "Stage.h"
#include "Player.h"

Goblin::Goblin() : Goblin(VGet(0,0,0), 0.0f) {}

Goblin::Goblin(const VECTOR& pos, float rot)
{
	const std::string folder = "data/model/Character/Goblin/";
	hModel = MV1LoadModel((folder + "Goblin.mv1").c_str());
	assert(hModel > 0);
	MV1SetupCollInfo(hModel);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	animator = new Animator(hModel);
	assert(animator != nullptr);

	animator->AddFile(A_NEUTRAL,   folder + "Anim_Neutral.mv1",   true);
	animator->AddFile(A_WALK,      folder + "Anim_Walk.mv1",      true);
	animator->AddFile(A_RUN,       folder + "Anim_Run.mv1",       true);
	animator->AddFile(A_ATTACK1,   folder + "Anim_Attack1.mv1",   false);
	animator->AddFile(A_DAMAGE,    folder + "Anim_Damage.mv1",    false);
	animator->AddFile(A_BLOW_IN,   folder + "Anim_Blow_In.mv1",   false);
	animator->AddFile(A_BLOW_LOOP, folder + "Anim_Blow_Loop.mv1", true);
	animator->AddFile(A_BLOW_OUT,  folder + "Anim_Blow_Out.mv1",  false);
	animator->AddFile(A_DOWN,      folder + "Anim_Down_Loop.mv1",      true);
	animator->Play(A_NEUTRAL);

	transform.position = pos;
	transform.rotation.y = rot;
	territory.center = pos;
	territory.range = 2000.0f;

	state = ST_WAIT;
}

Goblin::~Goblin()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}

	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Goblin::Update()
{
	animator->Update();

	switch (state)
	{
	case Goblin::ST_WAIT:
		UpdateWait();
		break;
	case Goblin::ST_DAMAGE:
		UpdateDamage();
		break;
	case Goblin::ST_CHASEA:
		UpdateChase();
		break;
	case Goblin::ST_ATTACK:
		UpdateAttack();
		break;
	case Goblin::ST_BACK:
		UpdateBack();
		break;
	}
	Stage* stage = FindGameObject<Stage>();
	VECTOR hit; // 地面の座標が入る関数
	VECTOR pos1 = transform.position + VGet(0, 100, 0);
	VECTOR pos2 = transform.position + VGet(0, -100, 0);
	if (stage->CollideLine(pos1, pos2, &hit))
	{
		transform.position = hit;
	}
}

void Goblin::CheckAttack(VECTOR3 p1, VECTOR3 p2)
{
	MV1RefreshCollInfo(hModel);
	MV1_COLL_RESULT_POLY ret = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (ret.HitFlag > 0)
	{
		animator->Play(A_DAMAGE);
		state = ST_DAMAGE;
	}
}

void Goblin::UpdateWait()
{
	Player* pl = FindGameObject<Player>();
	VECTOR3 flont = VECTOR3(0, 0, 1) * MGetRotY(transform.rotation.y);
	VECTOR3 toPlayer = pl->GetTransform().position - transform.position;
	float cosT = VDot(toPlayer.Normalize(),flont);

	// toPlayerの長さが1000以下
	if (toPlayer.Size() > 1000) return;

	if (cosT >= cos(60 * DegToRad))
	{
		// 視野に入ったらCHASEへ
		animator->Play(A_RUN);
		state = ST_CHASEA; // 仮
	}
}

void Goblin::UpdateDamage()
{
	if (animator->IsFinish())
	{
		animator->Play(A_NEUTRAL);
		state = ST_DAMAGE;
	}
}

void Goblin::UpdateChase()
{
	// プレイヤーに向かって走る
	// キャラの向いている向きに走る
	VECTOR3 velocity = VECTOR3(0, 0, 6) * MGetRotY(transform.rotation.y);
	transform.position += velocity;
	Player* pl = FindGameObject<Player>();
	VECTOR3 plPos = pl->GetTransform().position;
	VECTOR3 right = VECTOR3(1,0,0) * MGetRotY(transform.rotation.y); // 右ベクトル
	VECTOR3 toPlayer = plPos - transform.position;
	float ip = VDot(right, toPlayer);

	if (ip >= 0)
	{
		transform.rotation.y += DegToRad;
	}
	else
	{
		transform.rotation.y -= DegToRad;
	}

	// 近づいたらATTACKへ
	if (toPlayer.Size() < 100.0f)
	{
		animator->Play(A_ATTACK1);
		state = ST_ATTACK;
	}

	// テリトリーを出たらWAIT
	VECTOR3 v = transform.position - territory.center;
	if (v.Size() >= territory.range)
	{
		animator->Play(A_WALK);
		state = ST_BACK;
	}
}

void Goblin::UpdateAttack()
{
	// 攻撃アニメーションが終わったらWAITへ
	if (animator->IsFinish())
	{
		animator->Play(A_NEUTRAL);
		state = ST_WAIT;
	}
}

void Goblin::UpdateBack()
{
	VECTOR3 velocity = VECTOR3(0, 0, 2) * MGetRotY(transform.rotation.y);
	transform.position += velocity;
	VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y); // 右ベクトル
	VECTOR3 toBack = territory.center - transform.position;
	float ip = VDot(right, toBack);

	if (ip >= 0)
	{
		transform.rotation.y += DegToRad;
	}
	else
	{
		transform.rotation.y -= DegToRad;
	}

	if (toBack.Size() <= 150)
	{
		animator->Play(A_NEUTRAL);
		state = ST_WAIT;
	}
}

float Goblin::MoveTo(VECTOR3 target, float speed)
{
	VECTOR3 velocity = VECTOR3(0, 0, speed) * MGetRotY(transform.rotation.y);
	VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y); // 右ベクトル
	VECTOR3 toTagert = target - transform.position;
	float ip = VDot(right, toTagert);

	if (ip >= 0)
	{
		transform.rotation.y += DegToRad;
	}
	else
	{
		transform.rotation.y -= DegToRad;
	}

	return toTagert.Size();
}
