#pragma once
#include "../Library/GameObject.h"

class Object3D : public GameObject
{
public:
	Object3D();
	virtual ~Object3D();
	virtual void Update() override;
	virtual void Draw() override;
	const VECTOR& GetPositin() { return position; }
	const VECTOR& GetRotation() { return rotation; }

protected:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};