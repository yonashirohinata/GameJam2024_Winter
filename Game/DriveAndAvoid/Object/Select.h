#pragma once
#include "../Utility/Vector2D.h"
#include "../Object/Enemy.h"
#include "../Object/Player.h"

class Select
{
private:
	Vector2D location;		//�ʒu���
	Vector2D box_size;		//�����蔻��̑傫��
	bool flg;
	int time;				//�b��
	int damage;				//�摜
	int lean[5];		//���[���̏ꏊ
public:
	void Initialize();				//����������

	Select();
	~Select();
	void Update(Vector2D vector2D);
	Enemy* enemy;
	Player* player;
	void Draw();
	Vector2D GetLocation() const;		//�ʒu���̎擾
	Vector2D GetBoxSize() const;		//�����蔻��̑傫�����擾
};

