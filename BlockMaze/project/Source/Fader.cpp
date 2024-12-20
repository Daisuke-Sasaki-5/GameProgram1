#include "Fader.h"
#include "config.h"

Fader::Fader()
{
	alpha = 0;
}

Fader::~Fader()
{
}

void Fader::Update()
{
	if (timer < fadeTime) { // 終了時間を超えないように
		timer += 1.0f / 60.0f;

		// alphaを求める
		alpha = 255 / fadeTime * timer;
	}
}

void Fader::Draw()
{
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, alpha); // 半透明にする
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, fadeColor, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 半透明をやめる
}

void Fader::Fadeout(unsigned int color, float time)
{
	alpha = 0;
	fadeColor = color;
	fadeTime = time;
	timer = 0;
}

bool Fader::IsFinish()
{
	if (timer >= fadeTime) {
		return true;
	}
	return false;
}
