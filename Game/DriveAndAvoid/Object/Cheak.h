#pragma once
#include "../Utility/Vector2D.h"

class Cheak
{
private:
	Vector2D location;		//ˆÊ’uî•ñ
	Vector2D box_size;		//“–‚½‚è”»’è‚Ì‘å‚«‚³
	bool flg;
	int time;				//•b”

public:
	Cheak(int type);
	~Cheak();
	void Update(Vector2D vector2D);
	void Draw();
	Vector2D GetLocation() const;		//ˆÊ’uî•ñ‚Ìæ“¾
	Vector2D GetBoxSize() const;		//“–‚½‚è”»’è‚Ì‘å‚«‚³‚ğæ“¾
};

