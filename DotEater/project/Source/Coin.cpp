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
	VECTOR pPos = pl->GetPositin(); // �v���C���[�̑����̍��W
	pPos += VGet(0, 50, 0); // �R�C���Ɠ��������ɂ���

	if(gotten)
	{
		// ���ꂽ�̂ŁA�v���C���[�ɋ߂Â�
		// 1.�R�C������v���C���[�Ɍ������x�N�g�������
		VECTOR v = pPos - position;
		// 2.���̃x�N�g���̒�����5�̂��̂����
		v = VNorm(v) * 5.0f; // VNorm()�̓x�N�g���̒�����1�ɂ���֐�
		// 3.�R�C���̍��W�ɉ�����
		position += v;
		// 4.�R�C���ƃv���C���[�̋�����10�ȉ��ɂȂ�����DestoryMe()
		float diff = VSize(pPos - position);
		if (diff < 10.0f) // �R�C���ɓ������Ă�
		{
			DestroyMe();
		}
	}
	else {
		float diff = VSize(pPos - position);
		if (diff < 120.0f) // �R�C���ɓ������Ă�
		{
			gotten = true;
		}
	}
}
