#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f), angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr),player_alpha(0),alpha_flg(0)
{

}

Player::~Player()
{

}

//����������
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 5.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;
	player_alpha = 255;
	alpha_flg = FALSE;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/car1pol.bmp");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmp������܂���\n");
	}
}

//�X�V����
void Player::Update()
{
	//����s��Ԃł���΁A���M���񕜂�����
	if (!is_active)
	{
		angle += DX_PI_F / 4.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 6.0f)
		{
			is_active = true;
		}
		return;
	}

	//�R���̏���
	fuel -= speed;

	//�ړ�����
	Movement();

	//����������
	Acceleration();

	//����������
	Vanishment();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START)&& DX_INPUT_PAD1)
	{
		is_active = false;
	}

	//�o���A����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//�o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		//�o���A���Ԃ��o�߂��Ă������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//�`�揈��
void Player::Draw()
{
	//�����x�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, player_alpha);
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
	//�����x�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//�o���A����������Ă�����A�`����s��
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
}

//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//�����擾����
float Player::GetSpeed() const
{
	return this->speed;
}

//�R���擾����
float Player::GetFuel() const
{
	return this->fuel;
}

//�̗͎擾����
float Player::GetHp() const
{
	return this->hp;
}

//�o���A�����擾����
int Player::GetBarrierCount() const
{
	return this->barrier_count;
}

//�o���A�L�����H���擾
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

int Player::IsVanish()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		alpha_flg = TRUE;
	}

	return alpha_flg;
}

//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//�\���ړ�����
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		move += Vector2D(-5.0f, 0.0f);
		angle = -DX_PI_F / 18;
	}

	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(5.0f, 0.0f);
		angle = DX_PI_F / 18;
	}

	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -3.f);
	}

	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, 2.f);
	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

//����������
void Player::Acceleration()
{
	//LB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//RB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}

void Player::Vanishment()
{
	IsVanish();
	if (IsVanish() == TRUE && player_alpha >= 40)
	{
		player_alpha -= 5;
	}
}