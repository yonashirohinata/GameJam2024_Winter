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
	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/target.png");
}

void Enemy::Update(float speed)
{
	//�ړ�����
	Movement();
	//�^�[�Q�b�g�ꏊ�w��
	Target();
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, 0.0f);
	//�ʒu���Ɉړ��ʂ����Z����
	box_size += Vector2D(0.0f, 0.0f);
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
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_DPAD_LEFT))
	{
			move += Vector2D(-100.0f, 0.0f);
			cursor--;
	}
	
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_DPAD_RIGHT))
	{
		cursor++;
		move += Vector2D(100.0f, 0.0f);
	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
		
}
	
//�����蔻��̑傫�����擾
void Enemy::Target()
{
	Vector2D move2 = Vector2D(0.0f);

	//�ꏊ�w��i�P���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 50.0f)
	{
		move2 = Vector2D(location.x, 300.0f);
	}
	//�ꏊ�w��i�Q���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 150.0f)
	{
		move2 = Vector2D(150.0f, 300.0f);
	}
	////�ꏊ�w��i�R���[���j
	//if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 250.0f)
	//{
	//	box_size = Vector2D(250.0f, 300.0f);
	//}
	////�ꏊ�w��i�S���[���j
	//if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 350.0f)
	//{
	//	box_size = Vector2D(350.0f, 300.0f);
	//}
	////�ꏊ�w��i�T���[���j
	//if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 450.0f)
	//{
	//	box_size = Vector2D(450.0f, 300.0f);
	//}
	box_size += move2;
}