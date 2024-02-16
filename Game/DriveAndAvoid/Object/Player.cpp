#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f), angle(0.0f), 
speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr),player_alpha(0),alpha_flg(0)
,vanish_flg(nullptr),vanish_timer(0),bright{}
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
	speed = 7.0f;
	hp = 100;
	fuel = 20000;
	barrier_count = 3;
	player_alpha = 255;
	alpha_flg = FALSE;
	vanish_flg = FALSE;
	vanish_timer = 0;

	bright.red = 255;
	bright.green = 255;
	bright.blue = 255;

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
	//����s��Ԃł���΁A���g����]������
	if (!is_active)
	{
		angle += DX_PI_F / 4.0f;
		speed = 5;
		bright.red = 155;
		bright.green = 15;
		bright.blue = 5;
		if (angle >= DX_PI_F * 12.0f)
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
	if(!is_active)
	SetDrawBright(bright.red, bright.green,bright.blue);
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
	SetDrawBright(255, 255, 255);
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

//�̗͊Ǘ�����
void Player::ControlHp(float value)
{
	this->hp += value;
	if (hp > MAX_HP)
	{
		hp = MAX_HP;
	}
}

void Player::ControlFuel(float value)
{
	this->fuel += value;
	if (fuel > MAX_FUEL)
	{
		fuel = MAX_FUEL;
	}
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

//���������邩�H���擾
int Player::IsVanish()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		alpha_flg = TRUE;
		vanish_timer = 0;
		vanish_flg = false;
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
		move += Vector2D(-7.0f, 0.0f);
		angle = -DX_PI_F / 18;
	}

	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(7.0f, 0.0f);
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
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) || (location.y < box_size.y + 120) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

//����������
void Player::Acceleration()
{
	if (speed < 10.f)
	{
		speed += 1.f;
	}
}

//����������
void Player::Vanishment()
{
	IsVanish();
	//player�̓��ߒl��40�ُ�œ��߃��[�h���J�n�����Ȃ�
	if (IsVanish() == TRUE && player_alpha >= 40)
	{
		player_alpha -= 5;
	}
	else if (IsVanish() == TRUE && player_alpha <= 40)
	{
		//����������
		vanish_flg = true;
	}
	//���������������Ă���&�������̎��Ԃ�300�ȉ��Ȃ�
	if (vanish_flg == true && vanish_timer <= 300)
	{
		vanish_timer++;
	}
	//�������̉�������
	if (vanish_timer >= 300 && player_alpha <= 255)
	{
		alpha_flg = FALSE;
		player_alpha += 5;
	}
}