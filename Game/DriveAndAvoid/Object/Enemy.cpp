#include "Enemy.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"

Enemy::Enemy(int type, int handle) : type(type), image(handle), speed(0.0f), location(0.0f), box_size(0.0f)
{

}

Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	//出現させるX座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	location = Vector2D(250.0f,60.0f);
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	//速さの設定
	speed = (float)(this->type * 2);
	//画像の読み込み
	image = LoadGraph("Resource/images/target.png");
}

void Enemy::Update(float speed)
{
	//移動処理
	Movement();
	//ターゲット場所指定
	Target();
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, 0.0f);
	//位置情報に移動量を加算する
	box_size += Vector2D(0.0f, 0.0f);
}

void Enemy::Draw() const
{
	//敵画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Enemy::Finalize()
{

}

//敵のタイプを取得
int Enemy::GetType() const
{
	return type;
}

//位置情報を取得
Vector2D Enemy::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}

//移動処理
void Enemy::Movement()
{
	Vector2D move = Vector2D(0.0f);
	cursor = 3;
	time = 0;
	

	//十字移動処理
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

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
		
}
	
//当たり判定の大きさを取得
void Enemy::Target()
{
	Vector2D move2 = Vector2D(0.0f);

	//場所指定（１レーン）
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 50.0f)
	{
		move2 = Vector2D(location.x, 300.0f);
	}
	//場所指定（２レーン）
	if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 150.0f)
	{
		move2 = Vector2D(150.0f, 300.0f);
	}
	////場所指定（３レーン）
	//if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 250.0f)
	//{
	//	box_size = Vector2D(250.0f, 300.0f);
	//}
	////場所指定（４レーン）
	//if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 350.0f)
	//{
	//	box_size = Vector2D(350.0f, 300.0f);
	//}
	////場所指定（５レーン）
	//if (InputControl::GetButtonDown2(XINPUT_BUTTON_B) && location.x == 450.0f)
	//{
	//	box_size = Vector2D(450.0f, 300.0f);
	//}
	box_size += move2;
}