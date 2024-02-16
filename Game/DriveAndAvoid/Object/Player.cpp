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

//初期化処理
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

	//画像の読み込み
	image = LoadGraph("Resource/images/car1pol.bmp");

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
}

//更新処理
void Player::Update()
{
	//操作不可状態であれば、自身を回転させる
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

	//燃料の消費
	fuel -= speed;

	//移動処理
	Movement();

	//透明化処理
	Vanishment();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START)&& DX_INPUT_PAD1)
	{
		is_active = false;
	}

	//バリア処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//バリアが生成されていたら、更新を行う
	if (barrier != nullptr)
	{
		//バリア時間が経過していたか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//描画処理
void Player::Draw()
{
	//透明度設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, player_alpha);
	if(!is_active)
	SetDrawBright(bright.red, bright.green,bright.blue);
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
	SetDrawBright(255, 255, 255);
	//透明度を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//バリアが生成されていたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
}

//終了時処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力管理処理
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

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed() const
{
	return this->speed;
}

//燃料取得処理
float Player::GetFuel() const
{
	return this->fuel;
}

//体力取得処理
float Player::GetHp() const
{
	return this->hp;
}

//バリア枚数取得処理
int Player::GetBarrierCount() const
{
	return this->barrier_count;
}

//バリア有効か？を取得
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

//透明化するか？を取得
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

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//十字移動処理
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

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) || (location.y < box_size.y + 120) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

//加減速処理
void Player::Acceleration()
{
	if (speed < 10.f)
	{
		speed += 1.f;
	}
}

//透明化処理
void Player::Vanishment()
{
	IsVanish();
	//playerの透過値が40異常で透過モードが開始されるなら
	if (IsVanish() == TRUE && player_alpha >= 40)
	{
		player_alpha -= 5;
	}
	else if (IsVanish() == TRUE && player_alpha <= 40)
	{
		//透明化完了
		vanish_flg = true;
	}
	//透明化が完了している&透明化の時間が300以下なら
	if (vanish_flg == true && vanish_timer <= 300)
	{
		vanish_timer++;
	}
	//透明化の解除処理
	if (vanish_timer >= 300 && player_alpha <= 255)
	{
		alpha_flg = FALSE;
		player_alpha += 5;
	}
}