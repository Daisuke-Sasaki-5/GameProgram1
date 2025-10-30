#pragma once
#include "Object3D.h"
class Enemy; // Enemyってクラスがあるよ、includeとの違いは中身まで教えてもらえるが今回はポインタがほしいだけ
class EnemyManager : public Object3D
{
public:
	EnemyManager();
	~EnemyManager();

	bool RequestAttack(Enemy* e);
	void CancelAttack(Enemy* e);

private:
	std::list<Enemy*> waiting;
};