#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

#define MAX_FUEL 20000
#define MAX_HP 100

struct Bright
{
	int red;
	int green;
	int blue;
};
class Player
{
private:
	bool is_active;			//�L����Ԃ��H
	int image;				//�摜�f�[�^
	Vector2D location;		//�ʒu���W
	Vector2D box_size;		//�����蔻��̑傫��
	float angle;			//�p�x
	float speed;			//����
	float hp;				//�̗�
	float fuel;				//�R��
	int alpha_flg;			//�����x�͗L�����H
	bool vanish_flg;		//�����ɂȂ������H
	int vanish_timer;		//�������̎���
	int player_alpha;		//�v���C���[�̓����x
	int barrier_count;		//�o���A�̖���
	Barrier* barrier;		//�o���A
	Bright bright;			//���邳�����p
	
public:
	Player();
	~Player();

	void Initialize();		//����������
	void Update();			//�X�V����
	void Draw();			//�`�揈��
	void Finalize();		//�I��������

public:
	void SetActive(bool flg);			//�L���t���O�ݒ�
	void ControlHp(float value);		//�̗͌�������
	void ControlFuel(float value);		//�R���Ǘ�����
	Vector2D GetLocation() const;		//�ʒu���W�擾
	Vector2D GetBoxSize() const;		//�����蔻��̑傫���擾
	float GetSpeed() const;				//�����擾����
	float GetFuel() const;				//�R���擾
	float GetHp() const;				//�̗͎擾
	int GetBarrierCount()  const;		//�o���A�̖����擾
	bool IsBarrier()  const;			//�o���A�L�����H���擾
	int IsVanish();						//���������L�����H���擾
	void Acceleration();				//��������
	
private:
	void Movement();			//�ړ�����
	void Vanishment();			//����������
	void Damage();				//�_���[�W����
};