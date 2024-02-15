#include "Cheak.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Cheak::Cheak(int type)
{
	location = Vector2D(50.0f, 60.0f);
	location2 = Vector2D(150.0f, 60.0f);
	location3 = Vector2D(250.0f, 60.0f);
	location4 = Vector2D(350.0f, 60.0f);
	location5 = Vector2D(450.0f, 60.0f);
	attackflg = true;
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	flg = false;
	time = 0;
	/*damage = LoadGraph("Resource/images/dama.png");*/
}

Cheak::~Cheak()
{

}

void Cheak::Update(Vector2D vector2D)
{
	//ターゲット場所指定(大)
	StrongTarget();
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X)) {
		flg = true;
	}
	////場所指定（１レーン）
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x != vector2D.x)
	//{
	//	box_size = Vector2D(31.0f, 300.0f);
	//	flg = true;
	//}
	//ダメージが入るまでのタイマー
	if (flg == true) {
		time++;
	}

	if (time > 300) {
		time = 0;
		flg = false;
	}
	//ダメージ範囲内にいるか
	if (time > 50 && attackflg == false) {
		box_size = Vector2D(31.0f, 300.0f);
	}
	if (time > 100 && attackflg == false ) {
		box_size = Vector2D(31.0f, 60.0f);
		attackflg = true;
		location = Vector2D(50.0f, 60.0f);
		location2 = Vector2D(150.0f, 60.0f);
		location3 = Vector2D(250.0f, 60.0f);
		location4 = Vector2D(350.0f, 60.0f);
		location5 = Vector2D(450.0f, 60.0f);
	}
	//ダメージ範囲内にいるか
	if (time > 150) {
		box_size = Vector2D(31.0f, 300.0f);
	}
	else if (time > 250) {
		box_size = Vector2D(31.0f, 60.0f);
	}
	/*if (flg == true) {
		if (++time % 300 == 0) {
			box_size = Vector2D(31.0f, 60.0f);
			flg = false;
		}
	}*/
}

void Cheak::Draw() {
	/*DrawBox(location.x - 15, location.y, location.x + 15, location.y + 60, 0xffffff, false);*/
	/*if (time > 150) {
		DrawRotaGraphF(location.x, location.y + 200, 2.0, 0.0, damage, TRUE);
	}*/
}
//当たり判定代の移動場所
Vector2D Cheak::GetLocation() const
{
	return Vector2D();
}
//当たり判定大のボックス
Vector2D Cheak::GetBoxSize() const
{
	return Vector2D();
}

//ボタンを押したときの範囲攻撃（大）
void Cheak::StrongTarget()
{
	//場所指定（１レーン）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 50.0f)
	{
		location = NULL;
		attackflg = false;
	}
	
	//場所指定（２レーン）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 150.0f)
	{
		location2 = NULL;
		attackflg = false;
	}
	//場所指定（３レーン）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 250.0f)
	{
		location3 = NULL;
		attackflg = false;
	}
	//場所指定（４レーン）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 350.0f)
	{
		location4 = NULL;
		attackflg = false;
	}
	//場所指定（５レーン）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x == 450.0f)
	{
		location5 = NULL;
		attackflg = false;
	}

}
