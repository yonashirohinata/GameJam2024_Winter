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
	//�摜�̓ǂݍ���
	
	
	

}
//�`�揈��
void Item::Draw() const
{
	DrawGraphF(location.x,location.y, car_engine, TRUE);
}
