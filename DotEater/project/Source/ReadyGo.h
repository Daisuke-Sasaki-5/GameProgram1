#pragma once
#include "Object3D.h"

class ReadyGo : public Object3D
{
public:
	ReadyGo();
	~ReadyGo();
	void Update();
	void Draw();

	// Ready���I����������ׂ�AReady���I�������true
	bool TimeEnd();

	float timer;

private:
	int hReady;
	int hGo;
};