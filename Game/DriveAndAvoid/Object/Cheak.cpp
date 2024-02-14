#include "Cheak.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Cheak::Cheak(int type)
{
	switch (type)
	{
	case 0:
		location = Vector2D(50.0f, 60.0f);
		break;
	case 1:
		location = Vector2D(150.0f, 60.0f);
		break;
	case 2:
		location = Vector2D(250.0f, 60.0f);
		break;
	case 3:
		location = Vector2D(350.0f, 60.0f);
		break;
	case 4:
		location = Vector2D(450.0f, 60.0f);
		break;
	}
	
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
	//場所指定（１レーン）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X) && location.x != vector2D.x)
	{
		/*box_size = Vector2D(31.0f, 300.0f);*/
		flg = true;
	}
	//ダメージが入るまでのタイマー
	if (flg == true) {
		time++;
	}

	//if (time > 300) {
	//	time = 0;
	//	flg = false;
	//}
	////ダメージ範囲内にいるか
	//if (time > 150) {
	//	box_size = Vector2D(31.0f, 300.0f);
	//}
	//else if (time > 250) {
	//	box_size = Vector2D(31.0f, 60.0f);
	//}
	/*if (flg == true) {
		if (++time % 300 == 0) {
			box_size = Vector2D(31.0f, 60.0f);
			flg = false;
		}
	}*/
}

void Cheak::Draw() {
	DrawBox(location.x - 15, location.y, location.x + 15, location.y + 60, 0xffffff, false);
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
