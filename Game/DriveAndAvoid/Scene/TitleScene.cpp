#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : background_image(NULL), start_image(NULL), help_image(NULL), end_image(NULL), start_select_image(NULL), help_select_image(NULL), end_select_image(NULL), cursor_image(NULL), choose_se(NULL), select_se(NULL), title_bgm(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//����������
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/title2.png");
	start_image = LoadGraph("Resource/images/start_m.bmp");
	help_image = LoadGraph("Resource/images/help_m.bmp");
	end_image = LoadGraph("Resource/images/end_m.bmp");
	start_select_image = LoadGraph("Resource/images/start_yellow_m.bmp");
	help_select_image = LoadGraph("Resource/images/help_yellow_m.bmp");
	end_select_image = LoadGraph("Resource/images/end_yellow_m.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	//SE�̓ǂݍ���
	title_bgm = LoadSoundMem("Resource/sounds/runners_high.mp3");
	choose_se = LoadSoundMem("Resource/sounds/����{�^��������22.mp3");
	select_se = LoadSoundMem("Resource/sounds/����{�^��������23.mp3");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp������܂���\n");
	}
	if (start_image == -1)
	{
		throw("Resource/images/start_m.bmp������܂���\n");
	}
	if (help_image == -1)
	{
		throw("Resource/images/help_m.bmp������܂���\n");
	}
	if (end_image == -1)
	{
		throw("Resource/images/end_m.bmp������܂���\n");
	}
	if (start_select_image == -1)
	{
		throw("Resource/images/start_yellow_m.bmp������܂���\n");
	}
	if (help_select_image == -1)
	{
		throw("Resource/images/help_yellow_m.bmp������܂���\n");
	}
	if (end_select_image == -1)
	{
		throw("Resource/images/end_yellow_m.bmp������܂���\n");
	}
	if (choose_se == -1)
	{
		throw("Resource/sounds/����{�^��������22.mp3������܂���\n");
	}
	if (select_se == -1)
	{
		throw("Resource/sounds/����{�^��������22.mp3������܂���\n");
	}
	if (title_bgm == -1)
	{
		throw("Resource/sounds/runners_high.mp3������܂���\n");
	}
	ChangeVolumeSoundMem(255 * 45 / 100, title_bgm);
	PlaySoundMem(title_bgm, DX_PLAYTYPE_BACK, TRUE);

}

//�X�V����
eSceneType TitleScene::Update()
{
	
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN)|| InputControl::GetButtonDown2(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//1�ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 2)
		{
			menu_cursor = 0;
		}
	}

	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP) || InputControl::GetButtonDown2(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//1�ԏ�ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
	}

	//���ʉ�����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		PlaySoundMem(choose_se, DX_PLAYTYPE_BACK, TRUE);
	}

	//�J�[�\������i���肵����ʂɑJ�ڂ���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) || InputControl::GetButtonDown2(XINPUT_BUTTON_B))
	{
		PlaySoundMem(select_se, DX_PLAYTYPE_BACK, TRUE);

		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;

		case 1:
			return eSceneType::E_HELP;

		default:
			return eSceneType::E_END;
		}
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{

	//�^�C�g����ʂ̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�X�^�[�g�{�^���摜�̕`��
	if (menu_cursor == 0)
	{
		DrawGraph(120, 200, start_select_image, TRUE);
	}
	else
	{
		DrawGraph(120, 200, start_image, TRUE);
	}

	//�w���v�{�^���摜�̕`��
	if (menu_cursor == 1)
	{
		DrawGraph(101, 240, help_select_image, TRUE);
	}
	else
	{
		DrawGraph(101, 240, help_image, TRUE);
	}

	//�G���h�{�^���摜�̕`��
	if (menu_cursor == 2)
	{
		DrawGraph(80, 280, end_select_image, TRUE);
	}
	else
	{
		DrawGraph(80, 280, end_image, TRUE);
	}

	//�J�[�\���摜�̕`��
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);

}



//�I��������
void TitleScene::Finalize()
{
	//
	StopSoundMem(title_bgm);

	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(cursor_image);
	DeleteGraph(start_image);
	DeleteGraph(help_image);
	DeleteGraph(end_image);
	DeleteGraph(start_select_image);
	DeleteGraph(help_select_image);
	DeleteGraph(end_select_image);
	DeleteSoundMem(choose_se);
}

//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}