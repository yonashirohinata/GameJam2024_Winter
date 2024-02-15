#include "ResultScene.h"
#include "../Object/RankingData.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

ResultScene::ResultScene() : back_ground(NULL), player_win_se(NULL), score(0), fuel(0), hp(0), mileage(0)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

ResultScene::~ResultScene()
{

}

//����������
void ResultScene::Initialize()
{
	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back.bmp");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);

	player_win_se = LoadSoundMem("Resource/sounds/�h���h���p�t�p�t.mp3");

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmp������܂���\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmp������܂���\n");
	}
	if (player_win_se == -1)
	{
		throw("Resource/sounds/�h���h���p�t�p�t.mp3������܂���\n");
	}

	//�Q�[�����ʂ̓ǂݍ���
	ReadResultData();

	PlaySoundMem(player_win_se, DX_PLAYTYPE_BACK, TRUE);

}

//�X�V����
eSceneType ResultScene::Update()
{
	//B�{�^���Ń����L���O�ɑJ�ڂ���
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//�`�揈��
void ResultScene::Draw() const
{
	//�w�i�摜��`��
	DrawGraph(0, 0, back_ground, TRUE);

	//�X�R�A���\���̈�
	DrawBox(150, 150, 490, 330, GetColor(0, 153, 0), TRUE);
	DrawBox(150, 150, 490, 330, GetColor(0, 0, 0), FALSE);

	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);

	SetFontSize(32);
	if ((hp <= 0.0f || fuel <= 0.0f) && score / 10 < 3500)
	{
		DrawString(200, 160, "�v���C���[2WIN", GetColor(204, 0, 0));
	}
	else if((hp <= 0.0f || fuel <= 0.0f) && score / 10 >= 3500)
	{
		DrawString(200, 160, "�v���C���[1WIN", GetColor(204, 0, 0));
	}
	//��if���ŕ\��������W�Q���̂��
	//if(�ݒ肳�ꂽ��l > score || player->GetHp() < 0.0f)
	//DrawString(200, 160, "�W�Q��WIN", GetColor(204, 0, 0));
	SetFontSize(16);
	//DrawString(180, 200, "���s����     ", GetColor(0, 0, 0));
	//for (int i = 0; i < 3; i++)
	//{
	//	DrawRotaGraph(230, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[i], TRUE);
	//	DrawFormatString(260, 220 + (i * 21), GetColor(255, 255, 255), "%6d x %4d=%6d", enemy_count[i], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);
	//}
	SetFontSize(32);
	DrawString(180, 240, "���s����", GetColor(0, 0, 0));

	DrawFormatString(180, 240, 0xFFFFFF, "         =%6d", score / 10);

}

//�I��������
void ResultScene::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}
}

//���݂̃V�[�������擾
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

//���U���g�f�[�^�̓ǂݍ���
void ResultScene::ReadResultData()
{
	//�t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_date.csv���ǂݍ��߂܂���\n");
	}


	//���ʂ�ǂݍ���
	fscanf_s(fp, "%6d,\n", &score);

	//���������Ɠ��_���擾
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%6d,\n", &enemy_count[i]);
	}

	fscanf_s(fp, "%d,\n", &fuel);
	fscanf_s(fp, "%d,\n", &hp);
	fscanf_s(fp, "%d,\n", &mileage);

	//�t�@�C���N���[�Y
	fclose(fp);
}