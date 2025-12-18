#include "Board.h"

Board::Board()
{
	cells.resize(10); // 縦のサイズ
	for (int y = 0; y < cells.size(); y++)
	{
		cells[y].resize(15); // 横のサイズ
		for (int x = 0; x < cells[y].size(); x++)
		{
			if (x == 0 || y == 0 || y == cells.size() - 1 || x == cells[y].size() - 1)
			{
				cells[y][x].color = Wall;
			}
			else
			{
				cells[y][x].color = rand() % (Wall - Red);
			}
			cells[y][x].dy = 0;
		}
	}

	hImage = LoadGraph("data/puyo.png");
}

Board::~Board()
{
}

void Board::Update()
{
	int x, y;
	GetMousePoint(&x, &y);
	select.x = x / 32;
	select.y = y / 32;
	static bool prev = true;
	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		if (!prev)
		{
			// クリック位置が範囲外ならreturn
			if (select.y >= cells.size())return;
			if (select.x >= cells[select.y].size())return;

			// クリック位置が壁もしくは何もなかったらreturn
			if (cells[select.y][select.x].color == Wall)return;
			if (cells[select.y][select.x].color == No)return;

			Clear();

			if (Check(select.x, select.y) > 1)
			{
				Erase();
				Fall();
			}
		}
		prev = true;
	}
	else
	{
		prev = false;
	}

	for (int y = 0; y < cells.size(); y++)
	{
		for (int x = 0; x < cells[y].size(); x++)
		{
			if (cells[y][x].dy > 0)
			{
				cells[y][x].dy -= fallSpeed;
				if (cells[y][x].dy < 0)
				{
					cells[y][x].dy = 0;
				}
			}
		}
	}
	fallSpeed += 0.8f;

		// 落ちるブロックがなければ(全部のcellsのdyが0のとき)
	if (IsAll0())
	{
		for (int x = 1; x < cells[0].size() - 2; x++)
		{
			// 一番下に何もなければ
			if (cells[cells.size() - 2][x].color == No)
			{
				// 右側のものが1つ左に移動する
				for (int y = 1; y <= cells.size() - 1; y++)
				{
					cells[y][x] = cells[y][x + 1];
					cells[y][x + 1].color = No;
				}
			}
		}
	}

	// << ビットを右に移動    >> ビットを左に移動
	static const int U = (1 << 0);
	static const int D = (1 << 1);
	static const int L = (1 << 2);
	static const int R = (1 << 3);
	for (int y = 1; y < cells.size() - 1; y++)
	{
		for (int x = 1; x < cells[y].size() - 1; x++)
		{
			cells[y][x].connect = 0;
			if (cells[y][x].color == cells[y][x + 1].color)
			{
				cells[y][x].connect += R;
			}
			if (cells[y][x].color == cells[y][x - 1].color)
			{
				cells[y][x].connect += L;
			}
			if (cells[y][x].color == cells[y + 1][x].color)
			{
				cells[y][x].connect += D;
			}
			if (cells[y][x].color == cells[y - 1][x].color)
			{
				cells[y][x].connect += U;
			}
		}
	}
}

void Board::Draw()
{
	for (int y = 0; y < cells.size(); y++)
	{
		for (int x = 0; x < cells[y].size(); x++)
		{
			int c = cells[y][x].color;
			if (c >= Red)
			{
				int dy = cells[y][x].dy;
				int con = cells[y][x].connect;
				DrawRectGraph(x * 32, y * 32 - dy, c * 32, con * 32, 32, 32, hImage, TRUE);
			}
		}
	}

	DrawBox(select.x * 32, select.y * 32, (select.x + 1) * 32, (select.y + 1) * 32, GetColor(255, 255, 255), FALSE);
}

void Board::Clear()
{
	for (int y = 0; y < cells.size(); y++)
	{
		for (int x = 0; x < cells[y].size(); x++)
		{
			cells[y][x].erase = false;
		}
	}
}

int Board::Check(int x, int y)
{
	int num = 1; // 自分
	cells[y][x].erase = true;
	int col = cells[y][x].color; // 自分の色
	if (cells[y][x - 1].color == col && !cells[y][x - 1].erase)
	{
		num += Check(x - 1, y);
	}
	if (cells[y][x + 1].color == col && !cells[y][x + 1].erase)
	{
		num += Check(x + 1, y);
	}
	if (cells[y - 1][x].color == col && !cells[y - 1][x].erase)
	{
		num += Check(x, y - 1);
	}
	if (cells[y + 1][x].color == col && !cells[y + 1][x].erase)
	{
		num += Check(x, y + 1);
	}
	return num;
}

void Board::Erase()
{
	for (int y = 0; y < cells.size(); y++)
	{
		for (int x = 0; x < cells[y].size(); x++)
		{
			if (cells[y][x].erase)
				cells[y][x].color = No;
		}
	}
}

void Board::Fall()
{
	for (int x = 0; x < cells[0].size(); x++)
	{
		int fall = 0; // どれだけ空きがあるか
		for (int y = cells.size() - 1; y >= 0; y--)
		{
			if (cells[y][x].color == Wall)continue;
			if (cells[y][x].color == No)
			{
				fall++;
			}
			else if (fall > 0)
			{
				cells[y + fall][x] = cells[y][x]; // ブロックを下へ移動
				cells[y + fall][x].dy += fall * 32; // 落下距離
				cells[y][x].color = No; // 元の場所を空白化
			}
		}
	}
	fallSpeed = 0.0f;
}

bool Board::IsAll0()
{
	for (int y = 0; y < cells.size(); y++)
	{
		for (int x = 0; x < cells[y].size(); x++)
		{
			if (cells[y][x].dy != 0)
			{
				return false;
			}
		}
	}

	return true;
}
