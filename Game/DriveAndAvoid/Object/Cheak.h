#pragma once
#include "../Utility/Vector2D.h"

class Cheak
{
private:
	Vector2D location;		//�ʒu���
	Vector2D box_size;		//�����蔻��̑傫��
	bool flg;
	int time;				//�b��

public:
	Cheak(int type);
	~Cheak();
	void Update(Vector2D vector2D);
	void Draw();
	Vector2D GetLocation() const;		//�ʒu���̎擾
	Vector2D GetBoxSize() const;		//�����蔻��̑傫�����擾
};

