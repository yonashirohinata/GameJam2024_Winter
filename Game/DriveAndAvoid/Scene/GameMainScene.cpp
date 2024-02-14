#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>


GameMainScene::GameMainScene() : high_score(0), back_ground(NULL), barrier_image(NULL), car_engine_image(NULL), mileage(0), player(nullptr), enemy(nullptr), item(nullptr)

{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
		item_image[i] = NULL;
		item_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	//�����_�l��ǂݍ���
	ReadHighScore();

	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back.bmp");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	car_engine_image = LoadGraph("Resource/images/car_engine.png");
	oil_tank_image = LoadGraph("Resource/images/oil_tank.png");
	tool_box_image = LoadGraph("Resource/images/tool_box.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);
	/*car_engine_image = LoadGraph("Resource/images/car_engine.png");
	oil_tank_image = LoadGraph("Resource/images/oil_tank.png");
	tool_box_image = LoadGraph("Resource/images/tool_box.png");*/

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bpm������܂���\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bpm������܂���\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.png������܂���\n");
	}
	if (car_engine_image == -1)
	{
		throw("Resource/images/car_engine.png������܂���\n");
	}
	if (oil_tank_image == -1)
	{
		throw("Resource/images/oil_tank.png������܂���\n");
	}
	if (tool_box_image == -1)
	{
		throw("Resource/images/tool_box.png������܂���\n");
	}
	//�I�u�W�F�N�g�̐���
	player = new Player;
	enemy = new Enemy* [10];
	item = new Item* [10];
	for (int i = 0; i < 5; i++) {
	cheak[i] = new Cheak(i);
	}
	
	//�I�u�W�F�N�g�̏�����
	player->Initialize();

	item_image[0] = car_engine_image;
	item_image[1] = oil_tank_image;
	item_image[2] = tool_box_image;

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
		item[i] = nullptr;
	}
}

//�X�V����
eSceneType GameMainScene::Update()
{
	//�v���C���[�̍X�V
	player->Update();

	for (int i = 0; i < 5; i++) {
		if (enemy[0] != nullptr) {
			cheak[i]->Update(enemy[0]->GetLocation());
		}
	}
	

	//�ړ������̍X�V
	mileage += (int)player->GetSpeed() + 5;

	//�G��������
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < 1; i++)
		{
			if (enemy[i] == nullptr)
			{
				int type = GetRand(3) % 3;
				enemy[i] = new Enemy(type, enemy_image[type]);
				enemy[i]->Initialize();
				break;
			}
		}
	}
	//�A�C�e����������
	if (mileage / 40 % 100 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (item[i] == nullptr)
			{
				int item_type = GetRand(3) % 3;
				item[i] = new Item(item_type, item_image[item_type]);
				item[i]->Initialize();
				break;
			}
		}
	}



	for (int i = 0; i < 5; i++)
	{
		
			//�����蔻��̊m�F
			if (IsHitCheck2(player, cheak[i]))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				
			}
		
	}

	//�G�̍X�V�Ɠ����蔻��`�F�b�N
	//for (int i = 0; i < 10; i++)
	//{
	//	if (enemy[i] != nullptr)
	//	{
	//		enemy[i]->Update(player->GetSpeed());

	//		//��ʊO�ɍs������A�G���폜���ăX�R�A���Z
	//		if (enemy[i]->GetLocation().y >= 640.0f)
	//		{
	//			enemy_count[enemy[i]->GetType()] ++;
	//			enemy[i]->Finalize();
	//			delete enemy[i];
	//			enemy[i] = nullptr;
	//		}

	//		//�����蔻��̊m�F
	//		if (IsHitCheck(player, enemy[i]))
	//		{
	//			player->SetActive(false);
	//			player->DecreaseHp(-50.0f);
	//			enemy[i]->Finalize();
	//			delete enemy[i];
	//			enemy[i] = nullptr;
	//		}
	//	}
	//}
	//�A�C�e���̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 1; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Update(player->GetSpeed());

			//��ʊO�ɍs������A�G���폜���ăX�R�A���Z
			if (item[i]->GetLocation().y >= 640.0f)
			{
				item_count[item[i]->GetType()] ++;
				item[i]->Finalize();
				delete item[i];
				item[i] = nullptr;
			}

			//�����蔻��̊m�F
			if (IsHitCheck_item(player, item[i]))
			{
				/*player->SetActive(false);*/
				/*player->DecreaseHp(-50.0f);*/
				item[i]->Finalize();
				delete item[i];
				item[i] = nullptr;
			}
		}
	}

	//�v���C���[�̔R�����̗͂�0�����Ȃ�A���U���g�ɑJ�ڂ���
	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);

	//�G�̕`��
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}
	//�A�C�e���̕`��
	for (int i = 0; i < 10; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Draw();
		}
	}

	//�v���C���[�̕`��
	player->Draw();

	//UI�̕`��
	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	SetFontSize(16);
	DrawFormatString(510, 20, GetColor(0, 0, 0), "�W�Q��HIT������");
	//DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", �W�Q�������̕ϐ�);
	DrawFormatString(510, 80, GetColor(0, 0, 0), "�l������\n�A�C�e���̐�");
	//for (int i = 1; i < 3; i++)
	{
		//DrawRotaGraph(523 + (i * 50), 140, 0.3, 0, enemy_image[i], TRUE, FALSE);
		//DrawFormatString(510 + (i * 50), 160, GetColor(255, 255, 255), "%03d", enemy_count[i]);
	}
	DrawRotaGraph(520, 140, 0.7, 0, oil_tank_image, TRUE, FALSE);
	//DrawFormatString(510, 160, GetColor(255, 255, 255), "%03d", �A�C�e���J�E���g[i]);
	DrawRotaGraph(570, 140, 0.7, 0, car_engine_image, TRUE, FALSE);
	//DrawFormatString(510, 160, GetColor(255, 255, 255), "%03d", �A�C�e���J�E���g[2]);
	DrawRotaGraph(620, 140, 0.7, 0, tool_box_image, TRUE, FALSE);
	//DrawFormatString(510, 160, GetColor(255, 255, 255), "%03d", �A�C�e���J�E���g[3]);

	DrawFormatString(510, 220, GetColor(0, 0, 0), "�X�R�A");
	DrawFormatString(555, 240, GetColor(255, 255, 255), "%08d", mileage / 10);
	DrawFormatString(510, 260, GetColor(0, 0, 0), "�X�s�[�h");
	DrawFormatString(555, 280, GetColor(255, 255, 255), "%08.1f", player->GetSpeed());

	//�o���A�����̕`��
	for (int i = 0; i < player->GetBarrierCount(); i++)
	{
		DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	}

	//�o���A�����̕`��
	for (int i = 0; i < player->GetBarrierCount(); i++)
	{
		DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	}
	//�R���Q�[�W�̕`��
	float fx = 510.0f;
	float fy = 390.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	//�̗̓Q�[�W�̕`��
	fx = 510.0f;
	fy = 430.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);


	for (int i = 0; i < 5; i++) {
				cheak[i]->Draw();
	}

}

//�I��������
void GameMainScene::Finalize()
{
	//�X�R�A���v�Z����
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

	//���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���J���܂���\n");
	}

	//�X�R�A��ۑ�
	fprintf(fp, "%d,\n", score);

	//���������Ɠ��_��ۑ�
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	//���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}

	delete[] enemy;

	for (int i = 0; i < 10; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Finalize();
			delete item[i];
			item[i] = nullptr;
		}
	}

	delete[] item;
}

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//�n�C�X�R�A�̓ǂݍ���
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}

//�����蔻�菈���i�v���C���[�ƓG�j
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
	//�v���C���[���o���A��\���Ă�����A�����蔻��𖳎�����
	if (p->IsBarrier())
	{
		return false;
	}
	
	//�G��񂪖�����΁A�����蔻��𖳎�����
	if (e == nullptr)
	{
		return false;
	}

	
	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
	//������Ȃ�����T�C�Y�̑傫�����擾
	Vector2D box_ex2 = p->GetBoxSize() + e->GetBoxSize2();
	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
	//�R���W�����f�[�^���ʒu���ɍ����������Ă���Ȃ�A�m�[�q�b�g����Ƃ���
	return((fabsf(diff_location.x) > box_ex2.x) && (fabsf(diff_location.y) > box_ex2.y));
}
bool GameMainScene::IsHitCheck2(Player* p, Cheak* c)
{
	//�v���C���[���o���A��\���Ă�����A�����蔻��𖳎�����
	if (p->IsBarrier())
	{
		return false;
	}

	//�G��񂪖�����΁A�����蔻��𖳎�����
	if (c == nullptr)
	{
		return false;
	}


	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - c->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + c->GetBoxSize();
	
	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
	
}
//�����蔻�菈���i�v���C���[�ƃA�C�e���j
bool GameMainScene::IsHitCheck_item(Player* p, Item* i)
{
	////�v���C���[���o���A��\���Ă�����A�����蔻��𖳎�����
	//if (p->IsBarrier())
	//{
	//	return false;
	//}

	//�A�C�e����񂪖�����΁A�����蔻��𖳎�����
	if (i == nullptr)
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - i->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + i->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}
