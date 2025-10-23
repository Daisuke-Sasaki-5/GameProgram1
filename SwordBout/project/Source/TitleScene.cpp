#include "TitleScene.h"
#include <fstream>

TitleScene::TitleScene()
{
	// ==== セーブデータを保存 ====
	int a = 2000;
	//                  ↓保存するファイル名   ↓バイナリモード
	std::ofstream ofs("save.dat", std::ios::binary);
	ofs.write((char*)&a, sizeof(a));
					//↑ 変数を保存
	ofs.close(); // ファイルを閉じる

	// ==== セーブデータを読む ====
	int b = 0;
	std::ifstream ifs("save.dat", std::ios::binary);
	ifs.read((char*)&b, sizeof(b));
	ifs.close(); 
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
