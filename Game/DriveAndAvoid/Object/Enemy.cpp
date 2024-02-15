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
	////�o��������X���W�p�^�[�����擾
	//float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	location = Vector2D(250.0f,60.0f);
	location1 = Vector2D(50.0f, 60.0f);
	location2 = Vector2D(150.0f, 60.0f);
	location3 = Vector2D(250.0f, 60.0f);
	location4 = Vector2D(350.0f, 60.0f);
	location5 = Vector2D(450.0f, 60.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	//������Ȃ�����̏ꏊ�ݒ�
	No_box_size = Vector2D(31.0f, 60.0f);
	//�����̐ݒ�
	speed = (float)(this->type * 3);
	time = 0; //�ҋ@����
	time2 = 0;
	flg = false;
	//��������������i�P���[���̂݁j
	attackflg = true;
	//��������������i�R���[���p�j
	attackflg2 = true;
	lane1 = 0;
	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/target.png");
	
	damage = LoadGraph("Resource/images/dama.png");
	//���ӎ��̉摜
	Note = LoadGraph("Resource/images/Note.png");
	//�A�E�g�]�[���ɂ���Ƃ��̉摜
	Dangerous = LoadGraph("Resource/images/Dangerous.png");
	
}

void Enemy::Update(float speed)
{
	//�ړ�����
	Movement();
	//�^�[�Q�b�g�ꏊ�w��(��)
	WeakTarget();
	//�^�[�Q�b�g�ꏊ�w��(��)
	StrongTarget();
	//�_���[�W������܂ł̃^�C�}�[
	Timer();
	if (flg == true) {
		time++;
		time2++;
	}
	
	if (time > 150) {
		time = 0;
		time2 = 0;
		flg = false;
		location1 = Vector2D(50.0f, 60.0f);
		location2 = Vector2D(150.0f, 60.0f);
		location3 = Vector2D(250.0f, 60.0f);
		location4 = Vector2D(350.0f, 60.0f);
		location5 = Vector2D(450.0f, 60.0f);
	}
	
	//�_���[�W�͈͓��ɂ��邩
	if (time > 20 && attackflg == false ) {
		box_size = Vector2D(31.0f, 300.0f);	
	}
	if (time2 > 20 && attackflg2 == false) {
		box_size = Vector2D(100.0f, 300.0f);
	}
	if (time > 100 && attackflg == false || attackflg2 == false) {
		box_size = Vector2D(31.0f, 60.0f);
		attackflg = true;
		attackflg2 = true;
	}
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, 0.0f);
	////�ʒu���Ɉړ��ʂ����Z����
	//box_size += Vector2D(0.0f, 0.0f);
}

void Enemy::Draw() const
{
	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.5, 0.0, image, TRUE);
	if (time > 1 && time < 20 && attackflg == false || attackflg2 == false) {
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, Note, TRUE);
	}
	if (time > 20 && attackflg == false) {
		DrawRotaGraphF(location.x, location.y, 0.5, 0.0, Dangerous, TRUE);
		DrawRotaGraphF(location.x, location.y + 200, 1.0, 0.0, damage, TRUE);
	}
	if (time2 > 70 && attackflg2 == false) {
		DrawRotaGraphF(location.x, location.y, 0.5, 0.0, Dangerous, TRUE);
		DrawRotaGraphF(location.x, location.y + 200, 3.0, 0.0, damage, TRUE);
	}
	
	
	/*else if (time > 250) {
		DrawRotaGraphF(location.x, location.y + 200, 1.0, 0.0, bakuhatsu, TRUE);
	}*/
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



void Enemy::Timer() {
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) || InputControl::GetButtonDown(XINPUT_BUTTON_X)) {
		flg = true;
	}
}

//�ړ�����
void Enemy::Movement()
{
	Vector2D move = Vector2D(0.0f);
	cursor = 3;
	

	//�\���ړ�����
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_DPAD_LEFT) && attackflg == true
															 && attackflg2 == true)
	{
			move += Vector2D(-100.0f, 0.0f);
			cursor--;
	}
	
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_DPAD_RIGHT) && attackflg == true
															  && attackflg2 == true)
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
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 50.0f)
	{
		attackflg = false;
	}
	//�ꏊ�w��i�Q���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 150.0f)
	{
		attackflg = false;
	}
	//�ꏊ�w��i�R���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 250.0f)
	{
		attackflg = false;
	}
	//�ꏊ�w��i�S���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 350.0f)
	{
		attackflg = false;
	}
	//�ꏊ�w��i�T���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 450.0f)
	{
		attackflg = false;
	}
	
}

//�{�^�����������Ƃ��͈͍̔U���i��j
void Enemy::StrongTarget()
{
	//�ꏊ�w��i�P���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_X) && location.x == 50.0f)
	{
		location1 = NULL;
		attackflg2 = false;
	}

	//�ꏊ�w��i�Q���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_X) && location.x == 150.0f)
	{
		location2 = NULL;
		attackflg2 = false;
	}
	//�ꏊ�w��i�R���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_X) && location.x == 250.0f)
	{
		location3 = NULL;
		attackflg2 = false;
	}
	//�ꏊ�w��i�S���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_X) && location.x == 350.0f)
	{
		location4 = NULL;
		attackflg2 = false;
	}
	//�ꏊ�w��i�T���[���j
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_X) && location.x == 450.0f)
	{
		location5 = NULL;
		attackflg2 = false;
	}
	
}


