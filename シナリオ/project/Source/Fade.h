#pragma once
#include "../Library/GameObject.h"

class Fade : public GameObject
{
public:
	Fade();
	~Fade();
	void Update() override;
	void Draw() override;
	void FadeIn(std::string col, float time);
	void FadeOut(std::string col, float time);
	bool Finished();

private:
	float alpha; // •s“§–¾“x
	unsigned int color;
	float maxTime;
	float nowTime;
	float startAlpha;
	float endAlpha;
};