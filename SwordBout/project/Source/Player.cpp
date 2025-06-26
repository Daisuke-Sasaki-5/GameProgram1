#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "Camera.h"

Player::Player() : Player(VGet(0,0,0), 0.0f){}

Player::Player(const VECTOR3& pos, float rot)
{
	const std::string folder = "data/model/Character/Player/";
	// キャラモデルを読む
	hModel = MV1LoadModel((folder + "PC.mv1").c_str());
	assert(hModel > 0);
	// ルートノードをY軸回転する
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	animator = new Animator(hModel);
	assert(animator != nullptr);
	animator->AddFile(A_NEUTRAL,    folder + "Anim_Neutral.mv1",    true);
	animator->AddFile(A_RUN,        folder + "Anim_Run.mv1",        true);
	animator->AddFile(A_ATTACK1,    folder + "Anim_Attack1.mv1",    false);
	animator->AddFile(A_ATTACK2,    folder + "Anim_Attack2.mv1",    false);
	animator->AddFile(A_ATTACK3,    folder + "Anim_Attack3.mv1",    false);
	animator->AddFile(A_DAMAGE,     folder + "Anim_Damage.mv1",     false);
	animator->AddFile(A_BLOW_IN,    folder + "Anim_Blow_In.mv1",    false);
	animator->AddFile(A_BLOW_LOOP,  folder + "Anim_Blow_Loop.mv1",  true);
	animator->AddFile(A_BLOW_OUT,   folder + "Anim_Blow_Out.mv1",   false);
	animator->AddFile(A_DOWN,       folder + "Anim_Down_Loop.mv1",  true);
	animator->AddFile(A_GUARD_IN,   folder + "Anim_Guard_In.mv1",   false);
	animator->AddFile(A_GUARD_LOOP, folder + "Anim_Guard_Loop.mv1", true);
	animator->AddFile(A_GUARD_OUT,  folder + "Anim_Guard_Out.mv1",  false);
	animator->AddFile(A_JUMP_IN,    folder + "Anim_Jump_In.mv1",    false);
	animator->AddFile(A_JUMP_LOOP,  folder + "Anim_Jump_Loop.mv1",  true);
	animator->AddFile(A_JUMP_OUT,   folder + "Anim_Jump_Out.mv1",   false);
	animator->Play(A_NEUTRAL);

	transform.position = pos;
	transform.rotation.y = rot;

	camera = FindGameObject<Camera>();
}

Player::~Player()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
		hModel = -1;
	}
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
}

VECTOR3 moveVec;

void Player::Update()
{
	animator->Update();

	// 入力をベクトルに直す
	VECTOR3 intputVec = VECTOR3(0, 0, 0);
	if (CheckHitKey(KEY_INPUT_W))
	{
		intputVec += VECTOR3(0, 0, 1);
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		intputVec += VECTOR3(0, 0, -1);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		intputVec += VECTOR3(1, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		intputVec += VECTOR3(-1, 0, 0);
	}
	intputVec = intputVec.Normalize();

	// 進みたいベクトルを求める(実際に進むベクトル)
	// カメラの回転は、camera->GetTransform().rotationで手に入る
	if (intputVec.Size() > 0) {
		moveVec = intputVec * MGetRotY(camera->GetTransform().rotation.y);
		VECTOR3 front = VECTOR3(0, 0, 1) * MGetRotY(transform.rotation.y); // 前ベクトル
		VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y); // 右ベクトル
		float moveCos = VDot(moveVec, front);
		if (moveCos >= cosf(60.0f * DegToRad)) // 正面付近
		{
			transform.position += moveVec * 5.0f;
			transform.rotation.y = atan2f(moveVec.x, moveVec.z);
		}
		else if(VDot(moveVec,right) >= 0)
		{
			transform.rotation.y += 30.0f * DegToRad;
		}
		else
		{
			transform.rotation.y -= 30.0f * DegToRad;
		}
	}

	// 回転を合わせる(1フレームで60度回る) : 角度が合わなければ進まない

	// 角度があっていれば、その向きに進む

	camera->SetPlayerPosition(transform.position);
}

void Player::Draw()
{
	Object3D::Draw(); // キャラの表示
	DrawLine3D(transform.position + moveVec * 100, transform.position, GetColor(255, 0, 0));
}
