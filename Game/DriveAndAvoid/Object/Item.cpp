#include "Item.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"

Item::Item(int item_type, int handle) :type(item_type), image(handle), location(0.0f)
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
	location = Vector2D(random_x, 60.0f);
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	//速さの設定
	item_speed = /*(float)(this->type * 3)*/6;
	
	
	
	

}

void Item::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->item_speed + speed - 6);
}

//描画処理
void Item::Draw() const
{
	DrawGraphF(location.x,location.y, image, TRUE);
	DrawFormatString(location.x, location.y, 0xFFFFFF, "%d", image);
	/*DrawGraphF(location.x,location.y, oil_tank, TRUE);
	DrawGraphF(location.x,location.y, tool_box, TRUE);*/
}

void Item::Finalize()
{

}

int Item::GetType() const
{
	return /*this->*/type;
}

Vector2D Item::GetLocation() const
{
	return /*this->*/location;
}

Vector2D Item::GetBoxSize() const
{
	return /*this->*/box_size;
}