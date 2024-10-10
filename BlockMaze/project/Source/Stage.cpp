#include "Stage.h"

const int HEIGHT = 8;
const int WIDTH =  12;
const int CHIP_SIZE = 40;
int map[HEIGHT][WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");
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
				DrawRectGraph(x, y, 0, 40, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			}
			if (map[j][i] == 2) {
				DrawRectGraph(x, y, 120, 0, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			}
		}
	}
}
