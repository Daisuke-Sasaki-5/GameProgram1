#include "GoalText.h"
#include "..//Library/time.h"
#include "Fader.h"
#include "Player.h"
#include <math.h>

GoalText::GoalText()
{
	timer = 0.0f;
	fadeStarted = false;
	
}

GoalText::~GoalText()
{
}

int score = 1000;

void GoalText::Update()
{
	if (fadeStarted) {
		Fader* f = FindGameObject<Fader>();
		if (f->IsFinish()) {
			SceneManager::ChangeScene("TitleScene");
		}
		return; //FadeOut‚ªŽn‚Ü‚Á‚Ä‚¢‚é‚Ì‚ÅA‚±‚±‚æ‚è‰º‚Í‚â‚ç‚È‚¢
	}
	timer += Time::DeltaTime();
	if (timer >= 2.5f) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			Fader* f = FindGameObject<Fader>();
			f->Fadeout(GetColor(100, 100, 100), 1.0f);
			fadeStarted = true;
		//	SceneManager::ChangeScene("TitleScene");
		}
	}

}

void GoalText::Draw()
{
	Player* pl = FindGameObject<Player>();

	int size = GetFontSize();
	SetFontSize(50);
	DrawString(200, 200, "GAMEOVER", GetColor(25, 155, 0));
	if (timer >= 1.0f) {
		SetFontSize(25);
		int score = (pl->position.x - pl->startposition.x) / 40;
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%6d", score);
	}
	if (timer >= 2.0f) {
		DrawString(200, 500, "PUSU SPACE KEY", GetColor(255, 255, 255));
	}

	SetFontSize(size);
}
