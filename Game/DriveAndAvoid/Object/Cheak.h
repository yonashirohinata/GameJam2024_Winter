#pragma once
#include "../Utility/Vector2D.h"
#include "../Object/Enemy.h"
#include "../Object/Player.h"
class Cheak
{
private:
	Vector2D location;		//位置情報
	Vector2D box_size;		//当たり判定の大きさ
	bool flg;
	int time;				//秒数
	int damage;				//画像
public:
	Cheak(int type);
	~Cheak();
	void Update(Vector2D vector2D);
	Enemy* enemy;
	void Draw();
	Vector2D GetLocation() const;		//位置情報の取得
	Vector2D GetBoxSize() const;		//当たり判定の大きさを取得
};

