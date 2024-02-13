#include "Enemy.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"

Enemy::Enemy(int type, int handle) : type(type), image(handle), speed(0.0f), location(0.0f), box_size(0.0f)
{

}

Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	//�o��������X���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	location = Vector2D(250.0f,60.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	//�����̐ݒ�
	speed = (float)(this->type * 2);
}

void Enemy::Update(float speed)
{
	//�ړ�����
	Movement();
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, 0.0f);
}

void Enemy::Draw() const
{
	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Enemy::Finalize()
{

}

//�G�̃^�C�v���擾
int Enemy::GetType() const
{
	return type;
}

//�ʒu�����擾
Vector2D Enemy::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}

//�ړ�����
void Enemy::Movement()
{
	Vector2D move = Vector2D(0.0f);
	cursor = 3;
	time = 0;
	

	//�\���ړ�����
	if (InputControl::GetButton2(XINPUT_BUTTON_DPAD_LEFT))
	{
		time++;
		if (time > 5) {
		move += Vector2D(-100.0f, 0.0f);
		cursor--;
		time = 0; // �ҋ@���ԃ��Z�b�g
	}
	else {
			time = 0;
	}

	if (InputControl::GetButton2(XINPUT_BUTTON_DPAD_RIGHT))
	{
		cursor++;
		move += Vector2D(100.0f, 0.0f);
		time = 0;  // �ҋ@���ԃ��Z�b�g
	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
		
}
	
	
