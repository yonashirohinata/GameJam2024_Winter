#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : background_image(NULL), start_image(NULL), help_image(NULL), end_image(NULL), start_select_image(NULL), help_select_image(NULL), end_select_image(NULL), cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//����������
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Title.bmp");
	start_image = LoadGraph("Resource/images/start_m.bmp");
	help_image = LoadGraph("Resource/images/help_m.bmp");
	end_image = LoadGraph("Resource/images/end_m.bmp");
	start_select_image = LoadGraph("Resource/images/start_yellow_m.bmp");
	help_select_image = LoadGraph("Resource/images/help_yellow_m.bmp");
	end_select_image = LoadGraph("Resource/images/end_yellow_m.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

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
}

//�X�V����
eSceneType TitleScene::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN)|| InputControl::GetButtonDown2(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//1�ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 3)
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
			menu_cursor = 3;
		}
	}

	//�J�[�\������i���肵����ʂɑJ�ڂ���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) || InputControl::GetButtonDown2(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;

		case 1:
			return eSceneType::E_RANKING_DISP;

		case 2:
			return eSceneType::E_HELP;

		default:
			return eSceneType::E_END;
		}
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�J�[�\��Y���W�ʒu���擾

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
	if (menu_cursor == 2)
	{
		DrawGraph(101, 280, help_select_image, TRUE);
	}
	else
	{
		DrawGraph(101, 280, help_image, TRUE);
	}

	//�G���h�{�^���摜�̕`��
	if (menu_cursor == 3)
	{
		DrawGraph(80, 320, end_select_image, TRUE);
	}
	else
	{
		DrawGraph(80, 320, end_image, TRUE);
	}

	//�J�[�\���摜�̕`��
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}

//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(cursor_image);
	DeleteGraph(start_image);
	DeleteGraph(help_image);
	DeleteGraph(end_image);
	DeleteGraph(start_select_image);
	DeleteGraph(help_select_image);
	DeleteGraph(end_select_image);
}

//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}