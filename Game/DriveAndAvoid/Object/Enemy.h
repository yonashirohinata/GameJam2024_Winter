#pragma once

#include "../Utility/Vector2D.h"
#include "../Object/Player.h"

class Enemy
{
private:
	int type;				//�^�C�v
	int image;				//�摜
	int damage;				//�摜
	int bakuhatsu;			//�摜
	int lane1, lane2, lane3, lane4, lane5;     //���[���̏ꏊ
	float speed;			//����
	Vector2D location;		//�ʒu���
	Vector2D box_size;		//�����蔻��̑傫��
	Vector2D No_box_size;		//�����蔻��̑傫��
	int cursor;				//�J�[�\���̑I��
	int time;				//�ҋ@����
	bool flg;				//�t���O�i0.�I�t�A1.�I���j
public:
	Enemy(int type, int handle);
	~Enemy();

	void Initialize();				//����������
	void Update(float speed);		//�X�V����
	void Draw() const;				//�`�揈��
	void Finalize();				//�I��������

	int GetType() const;				//�^�C�v�̎擾
	Vector2D GetLocation() const;		//�ʒu���̎擾
	Vector2D GetBoxSize() const;		//�����蔻��̑傫�����擾
	void Timer();			//������Ȃ��Ƃ���ɂ��邩���擾
	void Cheaklane();		//���[���̔ԍ��𔻒�
private:
	void Movement();			//�ړ�����
	void WeakTarget();				//�^�[�Q�b�g�ꏊ�w��i���j
	void StrongTarget();				//�^�[�Q�b�g�ꏊ�w��i��j

};
