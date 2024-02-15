#pragma once

#include "../Utility/Vector2D.h"
#include "../Object/Player.h"

class Enemy
{
private:
	int type;				//�^�C�v
	int image;				//�摜
	int damage;				//�摜
	int Note;			//���ӎ��̉摜
	int	Dangerous;			//��Ȃ����̉摜
	int lane1, lane2, lane3, lane4, lane5;     //���[���̏ꏊ
	float speed;			//����
	Vector2D location;		//�ʒu���
	Vector2D location1;		//�ʒu���
	Vector2D location2;		//�ʒu���
	Vector2D location3;		//�ʒu���
	Vector2D location4;		//�ʒu���
	Vector2D location5;		//�ʒu���
	Vector2D box_size;		//�����蔻��̑傫��
	Vector2D No_box_size;		//�����蔻��̑傫��
	int cursor;				//�J�[�\���̑I��
	int time;				//�ҋ@����
	
	bool attackflg;			//�_���[�W�͈͓��ɂ��邩�i�P���[���̂݁j
	bool attackflg2;		//�_���[�W�͈͓��ɂ��邩�i�R���[���j
	int Damage;
public:
	bool flg;				//�t���O�ifalse.�I�t�Atrue.�I���j
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
