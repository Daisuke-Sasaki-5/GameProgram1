#pragma once
#include "Object3D.h"

class Camera : public Object3D {
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;

	void SetPlayerPosition(const VECTOR& pos);
private:
	VECTOR lookPosition;
	int prevMouseX, prevMouseY; // 前のマウスの位置記録
};