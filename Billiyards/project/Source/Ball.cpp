#include "Ball.h"
#include "Screen.h"

Ball::Ball(int num, VECTOR3 pos)
{
	hImage = LoadGraph("data/textures/billiyard.png");
	number = num;
	position = pos;
	velocity = VECTOR3(1, -0.5f, 0) * 10;
	velocity = VECTOR3(0, 0, 0);
	catched = false;
	addVelocity = VECTOR3(0, 0, 0);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	velocity += addVelocity;
	addVelocity = VECTOR3(0, 0, 0);

	if (number == 16)
	{
		if (catched)
		{
			// ���{�^���𗣂����̂�
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0)
			{
				int x, y;
				GetMousePoint(&x, &y);
				velocity = VECTOR3(catchX - x, catchY - y, 0) / 20.0f;
				catched = false;
			}
		}
		else
		{
			if (GetMouseInput() & MOUSE_INPUT_LEFT)
			{
				// ���N���b�N�����Ƃ��̍��W������Ă���
				catched = true;
				GetMousePoint(&catchX, &catchY);
			}
		}
	}

	// ����
	position += velocity;
	if (position.y >= Screen::HEIGHT - 28)
	{
		velocity.y *= -1;
	}
	if (position.y < 0 + 28)
	{
		velocity.y *= -1;
	}
	if (position.x >= Screen::WIDTH - 28)
	{
		velocity.x *= -1;
	}
	if (position.x < 0 + 28)
	{
		velocity.x *= -1;
	}
	// ���t���[�����ʌ��炷
	 // �x�N�g���̒��������߂�
	 // ���������l���炷
	 // ������0�ȉ��ɂȂ�΁Avelocity��(0,0,0)
	 // velocity���A���̒����ɏ��������適velocity�̒�����1�ɂ��Ă���A�������|����

	float len = velocity.Size(); // �x�N�g���̒��������߂�
	len -= 0.01f;
	if (len <= 0)
	{
		velocity = VECTOR3(0, 0, 0);
	}
	else
	{
		VECTOR3 n = velocity.Normalize(); // �x�N�g���̒�����1�ɂ��� 
		// n�͌��������߂Ă���
		velocity = n * len;
	}
}

void Ball::Draw()
{
	int x = (number - 1) % 4;
	int y = (number - 1) / 4;
	DrawRectGraph(position.x - 32, position.y - 32, x * 64, y * 64, 64, 64, hImage, TRUE);
}

void Ball::AddForce(VECTOR3 force)
{
	addVelocity += force;
}

void Ball::HitOtherBall(Ball* other)
{
	// �@�������Ă��邩���ׂ�
	VECTOR3 otherPos = other->GetPosition();
	VECTOR3 v = otherPos - position;
	if (v.Size() <= 60.0f)
	{
		float pushLen = 60.0f - v.Size();
		position -= v.Normalize() * pushLen;
		// ����ɓn���x�N�g�������߂�
		VECTOR3 a = velocity; // a�x�N�g���͎����̈ړ����x
		VECTOR3 b = v.Normalize(); // ����ւ̃x�N�g���̒���1
		float len = VDot(a, b); // ���ς��A����ւ̗͂̑傫��
		// ����֓n���x�N�g��
		// �������������瑊��ւ̌���
		// ������len
		other->AddForce(b * len);
		AddForce(b * (-len));
	}
}
