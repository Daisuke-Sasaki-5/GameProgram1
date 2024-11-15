#include "Stage.h"
#include "Player.h"
#include "Coin.h"
#include "stage1.h"

// 1 = レンガ　2 = コイン　9 = プレイヤー
const int CHIP_SIZE = 40;

Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			if (map[j][i] == 9) {
				Player* p = Instantiate<Player>();
				p->position.x = 100 + i * 40;
				p->position.y = 100 + j * 40;
			}
			if (map[j][i] == 2) {
				Coin* c = Instantiate<Coin>();
				c->position.x = 100 + i * 40;
				c->position.y = 100 + j * 40;
			}

		}
	}
	scroll = 0;
}

Stage::~Stage()
{
}

void Stage::Draw()
{
	for (int j = 0; j < HEIGHT; j++) {
		int y = 100 + j * 40;
		for (int i = 0; i < WIDTH; i++) {
			int x = 100 + i * 40;
			if (map[j][i] == 1) {
				DrawRectGraph(x - scroll, y, 0, 40, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			}
			if (map[j][i] == 8) {
				DrawRectGraph(x - scroll, y, 160, 0, 40, 40, hImage, TRUE);
			}
			//if (map[j][i] == 2) {
			//	DrawRectGraph(x, y, 120, 0, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			//}
		}
	}
}

int Stage::IsWallRight(VECTOR2 pos)
{
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1 ) {
		int push = ((int)pos.x - 100) % 40 + 1;
		return push;
	}
	return 0;
}

int Stage::IsWallDown(VECTOR2 pos)
{
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1) {
		int push = ((int)pos.y - 100) % 40 + 1;
		return push;
	}
	return 0;
}

int Stage::IsWallLeft(VECTOR2 pos)
{
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1) {
		int push = 40 - ((int)pos.x - 100) % 40;
		return push;
	}
	return 0;
}

int Stage::IsWallUp(VECTOR2 pos)
{
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1) {
		int push = 40 - ((int)pos.y - 100) % 40;
		return push;
	}
	return 0;
}

bool Stage::IsGoal(VECTOR2 pos)
{
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 8) {
		return true;
	}
	return false;
}
