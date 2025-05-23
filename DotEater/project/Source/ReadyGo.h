#pragma once
#include "Object3D.h"

class ReadyGo : public Object3D
{
public:
	ReadyGo();
	~ReadyGo();
	void Update();
	void Draw();

	// Readyが終わったか調べる、Readyが終わったらtrue
	bool TimeEnd();

	float timer;

private:
	int hReady;
	int hGo;
};