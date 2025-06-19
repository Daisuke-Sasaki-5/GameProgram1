#include "PlayScene.h"
#include "BallManager.h"
#include "Ball.h"
#include <DxLib.h>

PlayScene::PlayScene()
{
	new Ball(1, VECTOR3(100, 200, 0));
	new Ball(3, VECTOR3(200, 300, 0));
	new Ball(4, VECTOR3(300, 400, 0));
	new Ball(5, VECTOR3(400, 500, 0));
	new Ball(6, VECTOR3(600, 600, 0));
	new Ball(16, VECTOR3(500, 500, 0));
	new BallManager();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
