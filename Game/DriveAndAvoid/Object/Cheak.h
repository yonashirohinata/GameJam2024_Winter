#pragma once
#include "../Utility/Vector2D.h"
#include "../Object/Enemy.h"
#include "../Object/Player.h"
class Cheak
{
private:
	Vector2D location;		//�ʒu���
	Vector2D location2;		//�ʒu���
	Vector2D location3;		//�ʒu���
	Vector2D location4;		//�ʒu���
	Vector2D location5;		//�ʒu���
	Vector2D box_size;		//�����蔻��̑傫��
	bool flg;
	int time;				//�b��
	int damage;				//�摜
	bool attackflg;
public:
	Cheak(int type);
	~Cheak();
	void Update(Vector2D vector2D);
	Enemy* enemy;
	void Draw();
	Vector2D GetLocation() const;		//�ʒu���̎擾
	Vector2D GetBoxSize() const;		//�����蔻��̑傫�����擾

private:
	void StrongTarget();				//�^�[�Q�b�g�ꏊ�w��i��j
};

