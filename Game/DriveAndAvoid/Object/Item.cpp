#include "Item.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"

Item::Item(int item_type, int handle) :car_engine(NULL), oil_tank(NULL), tool_box(NULL), location(0.0f)
{

}

Item::~Item()
{

}

//����������
void Item::Initialize()
{   //�o��������X���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	location = Vector2D(250.0f, 60.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	//�����̐ݒ�
	item_speed = (float)(this->item_type * 2);
	
	
	
	

}

void Item::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->item_speed + speed - 6);
}

//�`�揈��
void Item::Draw() const
{
	DrawGraphF(location.x,location.y, car_engine, TRUE);
	DrawGraphF(location.x,location.y, oil_tank, TRUE);
	DrawGraphF(location.x,location.y, tool_box, TRUE);
}

void Item::Finalize()
{

}

int Item::GetType() const
{
	return /*this->*/item_type;
}

Vector2D Item::GetLocation() const
{
	return /*this->*/location;
}

Vector2D Item::GetBoxSize() const
{
	return /*this->*/box_size;
}