#pragma once
#include "../Utility/Vector2D.h"
#include "../Object/Enemy.h"
#include "../Object/Player.h"

class Select
{
private:
	Vector2D location;		//ˆÊ’uî•ñ
	Vector2D box_size;		//“–‚½‚è”»’è‚Ì‘å‚«‚³
	bool flg;
	int time;				//•b”
	int damage;				//‰æ‘œ
	int lean[5];		//ƒŒ[ƒ“‚ÌêŠ
public:
	void Initialize();				//‰Šú‰»ˆ—

	Select();
	~Select();
	void Update(Vector2D vector2D);
	Enemy* enemy;
	Player* player;
	void Draw();
	Vector2D GetLocation() const;		//ˆÊ’uî•ñ‚Ìæ“¾
	Vector2D GetBoxSize() const;		//“–‚½‚è”»’è‚Ì‘å‚«‚³‚ğæ“¾
};

