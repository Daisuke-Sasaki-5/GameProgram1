#pragma once
#include "Enemy.h"
#include "Animator.h"

class Goblin : public Enemy {
public:
	Goblin();
	Goblin(const VECTOR& pos, float rot);
	~Goblin();
	void Update() override;
	void CheckAttack(VECTOR3 p1, VECTOR3 p2)override;
	void Draw() override;

private:
	enum AnimID {
		A_NEUTRAL = 0,
		A_WALK,
		A_RUN,
		A_ATTACK1,
		A_DAMAGE,
		A_BLOW_IN,
		A_BLOW_LOOP,
		A_BLOW_OUT,
		A_DOWN,
	};
	Animator* animator;

	int hAxe;
	VECTOR axeBtm;
	VECTOR axeTop;

	enum State {
		ST_WAIT = 0, // ‘Ò‹@
		ST_DAMAGE,
		ST_CHASEA,
		ST_ATTACK,
		ST_BACK,
	};
	State state;
	void UpdateWait();
	void UpdateDamage();
	void UpdateChase();
	void UpdateAttack();
	void UpdateBack();

	struct CircleRange {
		VECTOR center;
		float range;
	};
	CircleRange territory;
	float MoveTo(VECTOR3 target, float speed);
};