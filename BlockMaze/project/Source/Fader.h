#pragma once
#include "../Library/gameObject.h"

class Fader : public GameObject {
public:
	Fader();
	~Fader();
	void Update();
	void Draw();
	void Fadeout(unsigned int color, float time);
	bool IsFinish();

	float alpha;
	unsigned int fadeColor;
	float fadeTime; // �t�F�[�h�A�E�g���鎞��
	float timer; // ���ۂ̌o�ߎ���
};