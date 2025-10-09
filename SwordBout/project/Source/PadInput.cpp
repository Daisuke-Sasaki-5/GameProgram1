#include "PadInput.h"
#include <cassert>

PadInput::PadInput(int id)
{
	padId = id;
	DontDestroyOnSceneChange();
}

PadInput::~PadInput()
{
}

void PadInput::Update()
{
	for (int i = 0; i < 16; i++)
	{
		prevButtons[i] = input.Buttons[i];
	}
	GetJoypadXInputState(padId, &input);
	if (CheckHitKey(KEY_INPUT_M))
	{
		input.Buttons[XINPUT_BUTTON_A] = 1;
	}
}

void PadInput::Draw()
{
	DrawFormatString(200, 50, GetColor(255, 255, 255), "LStick %d %d", input.ThumbLX, input.ThumbLY);
}

static const int MAX = 32767;
static const int ZERO_RANGE = MAX / 5;
float PadInput::LStickX()
{
	if (input.ThumbLX >= ZERO_RANGE)
	{
		float ret = (float)(input.ThumbLX - ZERO_RANGE) / (MAX - ZERO_RANGE);
		if (ret > 1.0f)
		{
			ret = 1.0f;
		}
		return ret;
	}
	else if (input.ThumbLX <= -ZERO_RANGE)
	{
		float ret = (float)(input.ThumbLX + ZERO_RANGE) / (MAX - ZERO_RANGE);
		if (ret < -1.0f)
		{
			ret = -1.0f;
		}
		return ret;
	}
	return 0.0f;
}

float PadInput::LStickY()
{
	if (input.ThumbLY >= ZERO_RANGE)
	{
		float ret = (float)(input.ThumbLY - ZERO_RANGE) / (MAX - ZERO_RANGE);
		if (ret > 1.0f)
		{
			ret = 1.0f;
		}
		return ret;
	}
	else if (input.ThumbLY <= -ZERO_RANGE)
	{
		float ret = (float)(input.ThumbLY + ZERO_RANGE) / (MAX - ZERO_RANGE);
		if (ret < -1.0f)
		{
			ret = -1.0f;
		}
		return ret;
	}
	return 0.0f;
}

float PadInput::RStickX()
{
	if (input.ThumbRX >= ZERO_RANGE)
	{
		float ret = (float)(input.ThumbRX - ZERO_RANGE) / (MAX - ZERO_RANGE);
		if (ret > 1.0f)
		{
			ret = 1.0f;
		}
		return ret;
	}
	else if (input.ThumbRX <= -ZERO_RANGE)
	{
		float ret = (float)(input.ThumbRX + ZERO_RANGE) / (MAX - ZERO_RANGE);
		if (ret < -1.0f)
		{
			ret = -1.0f;
		}
		return ret;
	}
	return 0.0f;
}

float PadInput::RStickY()
{
	if (input.ThumbRY >= ZERO_RANGE)
	{
		float ret = (float)(input.ThumbRY - ZERO_RANGE) / (MAX - ZERO_RANGE);
		if (ret > 1.0f)
		{
			ret = 1.0f;
		}
		return ret;
	}
	else if (input.ThumbRY <= -ZERO_RANGE)
	{
		float ret = (float)(input.ThumbRY + ZERO_RANGE) / (MAX - ZERO_RANGE);
		if (ret < -1.0f)
		{
			ret = -1.0f;
		}
		return ret;
	}
	return 0.0f;
}

VECTOR2 PadInput::LStickVec()
{
	VECTOR2 ret = VECTOR2(LStickX(), LStickY());
	if (CheckHitKey(KEY_INPUT_W))
	{
		ret += VECTOR2(0, 1);
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		ret += VECTOR2(0, -1);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		ret += VECTOR2(1, 0);
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		ret += VECTOR2(-1, 0);
	}
	if (ret.Size() > 1.0f)
	{
		ret = ret.Normalize();
	}
	return ret;
}

bool PadInput::Press(int id)
{
	assert(id < 16);
	return input.Buttons[id] > 0;
}

bool PadInput::OnPush(int id)
{
	assert(id < 16);
	return input.Buttons[id] > 0 && prevButtons[id] == 0;
}
