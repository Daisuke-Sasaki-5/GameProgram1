#pragma once
#include "Object3D.h"

class ReadyGo : public Object3D
{
public:
	ReadyGo();
	~ReadyGo();
	void Update();
	void Draw();

	// Ready‚ªI‚í‚Á‚½‚©’²‚×‚éAReady‚ªI‚í‚Á‚½‚çtrue
	bool TimeEnd();

	float timer;

private:
	int hReady;
	int hGo;
};