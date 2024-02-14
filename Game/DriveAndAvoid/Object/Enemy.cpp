#include "Enemy.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"

Enemy::Enemy(int type, int handle) : type(type), image(handle), speed(0.0f), location(0.0f), box_size(0.0f), No_box_size(0.0f),time(true)
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
	//������Ȃ�����̏ꏊ�ݒ�
	No_box_size = Vector2D(31.0f, 60.0f);
	//�����̐ݒ�
	speed = (float)(this->type * 3);
	time = 0; //�ҋ@����
	flg = false;
	lane1 = 0;
	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/target.png");
	
	damage = LoadGraph("Resource/images/dama.png");
	bakuhatsu = LoadGraph("Resource/images/bakuhatsu.png");
	
}

void Enemy::Update(float speed)
{
	//�ړ�����
	Movement();
	//�^�[�Q�b�g�ꏊ�w��(��)
	WeakTarget();
	//�^�[�Q�b�g�ꏊ�w��(��)
	StrongTarget();
	/*Timer();
	
	if (Timer() == true) {
		time++;
	}*/
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, 0.0f);
	////�ʒu���Ɉړ��ʂ����Z����
	//box_size += Vector2D(0.0f, 0.0f);
}

void Enemy::Draw() const
{
	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.5, 0.0, image, TRUE);
	if (InputControl::GetButton(XINPUT_BUTTON_X)) {
		DrawRotaGraphF(location.x, location.y + 200, 3.0, 0.0, damage, TRUE);
	}
	else if (InputControl::GetButton(XINPUT_BUTTON_A)) {
		DrawRotaGraphF(location.x, location.y + 200, 1.0, 0.0, damage, TRUE);
	}
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

//������Ȃ�����̑傫�����擾
Vector2D Enemy::GetBoxSize2() const
{
	return No_box_size;
}

//�ҋ@����
//bool Enemy::Timer()
//{
//	
//	if (InputControl::GetButtonDown(XINPUT_BUTTON_A)) {
//		flg = true;
//	}
//}

//void Enemy::Cheaklane() {
//	if (location.x == 50.0f) {
//		return lane1;
//	}
//
//}
//�ړ�����
void Enemy::Movement()
{
	Vector2D move = Vector2D(0.0f);
	cursor = 3;
	

	//�\���ړ�����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
			move += Vector2D(-100.0f, 0.0f);
			cursor--;
	}
	
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
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
	
//�{�^�����������Ƃ��͈͍̔U���i���j
void Enemy::WeakTarget()
{

	//�ꏊ�w��i�P���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) && location.x == 50.0f)
	{
		if (time > 10) {
			box_size = Vector2D(31.0f, 300.0f);
		}
	}
	//�ꏊ�w��i�Q���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) && location.x == 150.0f)
	{
		box_size = Vector2D(31.0f, 300.0f);
	}
	//�ꏊ�w��i�R���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) && location.x == 250.0f)
	{
		box_size = Vector2D(31.0f, 300.0f);
	}
	//�ꏊ�w��i�S���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) && location.x == 350.0f)
	{
		box_size = Vector2D(31.0f, 300.0f);
	}
	//�ꏊ�w��i�T���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) && location.x == 450.0f)
	{
		box_size = Vector2D(31.0f, 300.0f);
	}
	
}

//�{�^�����������Ƃ��͈͍̔U���i��j
void Enemy::StrongTarget()
{
	//�ꏊ�w��i�P���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 50.0f)
	{
		box_size = Vector2D(250.0f, 300.0f);
		No_box_size = Vector2D(31.0f, 300.0f);
	}
	//�ꏊ�w��i�Q���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 150.0f)
	{
		box_size = Vector2D(250.0f, 300.0f);
		No_box_size = Vector2D(31.0f, 300.0f);
	}
	//�ꏊ�w��i�R���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 250.0f)
	{
		box_size = Vector2D(250.0f, 300.0f);
		No_box_size = Vector2D(31.0f, 300.0f);
	}
	//�ꏊ�w��i�S���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 350.0f)
	{
		box_size = Vector2D(250.0f, 300.0f);
		No_box_size = Vector2D(31.0f, 300.0f);
	}
	//�ꏊ�w��i�T���[���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 450.0f)
	{
		box_size = Vector2D(400.0f, 300.0f);
		No_box_size = Vector2D(31.0f, 300.0f);
	}
	
}


