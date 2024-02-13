#include "Item.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"

Item::Item(int item_type, int handle) :car_engine(NULL), oil_tank(NULL), tool_box(NULL), location(0.0f)
{

}

Item::~Item()
{

}

//初期化処理
void Item::Initialize()
{   //出現させるX座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	location = Vector2D(250.0f, 60.0f);
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	//画像の読み込み
	
	
	

}
//描画処理
void Item::Draw() const
{
	DrawGraphF(location.x,location.y, car_engine, TRUE);
}
