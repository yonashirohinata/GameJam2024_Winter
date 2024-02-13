#pragma once

#include "../Utility/Vector2D.h"
class Item
{
private:
	int item_type;				//�^�C�v
	int item_image;				//�摜
	float item_speed;			//����
	Vector2D location;		//�ʒu���
	Vector2D box_size;		//�����蔻��̑傫��

	int car_engine;
	int oil_tank;
	int tool_box;

public:
	Item(int item_type,int handle);
	~Item();

	void Initialize();				//����������
	void Update(float speed);		//�X�V����
	void Draw() const;				//�`�揈��
	void Finalize();				//�I��������

	int GetType() const;				//�^�C�v�̎擾
	Vector2D GetLocation() const;		//�ʒu���̎擾
	Vector2D GetBoxSize() const;		//�����蔻��̑傫�����擾
};