#include "Coin.h"
#include "Player.h"
#include "config.h"

const int CHIP_SIZE = 40;

Coin::Coin()
{
	hImage = LoadGraph("data/image/parts.png");
	got = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	if (got) {
		counter -= 1;
		if (counter == 0)
		{
			DestroyMe();
		}
		return;
	}
	Player* p = FindGameObject<Player>(); //����̃C���X�^���X���擾
	VECTOR2 playerPos = p->position; // ����̍��W���擾
	if (CircleHit(playerPos, position, 40)) // �~�̓����蔻��
	{
		got = true;
		counter = 20;
	}
}

void Coin::Draw()
{
	DrawRectGraph(position.x, position.y, 120, 0, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
}
