#pragma once
#include "../Library/GameObject.h"

class PadInput : public GameObject
{
public:
	PadInput(int id);
	~PadInput();
	void Update() override;
	void Draw() override;

	float LStickX();
	float LStickY();
	float RStickX();
	float RStickY();

	VECTOR2 LStickVec();

	bool Press(int id); // ‰Ÿ‚³‚ê‚Ä‚é
	bool OnPush(int id); // ‰Ÿ‚µ‚½uŠÔ

private:
	int padId;
	XINPUT_STATE input;
	unsigned char prevButtons[16]; //  ‘O‚Ìƒ{ƒ^ƒ“
};