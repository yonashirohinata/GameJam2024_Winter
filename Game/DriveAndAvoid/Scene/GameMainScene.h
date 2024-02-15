#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Object/Item.h"
#include "../Object/Cheak.h"
class GameMainScene : public SceneBase
{
private:
	int high_score;			//�n�C�X�R�A
	int back_ground;		//�w�i�摜
	int barrier_image;		//�o���A�摜
	int car_engine_image;	//�����A�C�e���摜
	int oil_tank_image;		//�R���A�C�e���摜
	int tool_box_image;		//HP�񕜃A�C�e���摜
	int mileage;			//���s����
	int enemy_image[3];		//�G�摜
	int enemy_count[3];		//�ʂ肷�����G�J�E���g
	int item_image[3];
	int item_count[3];
	
	int main_bgm;
	int heal_se;
	int damage_se;

	Player* player;			//�v���C���[
	Enemy** enemy;			//�G
	Item** item;             //�A�C�e��
	Cheak* cheak[5];			//����


public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//�n�C�X�R�A�ǂݍ��ݏ���
	void ReadHighScore();

	void Recover();

	//�����蔻��
	bool IsHitCheck(Player* p, Enemy* e);

	bool IsHitCheck2(Player* p, Cheak* c);
	bool IsHitCheck_item(Player* p, Item* i);
};