#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//����������
void HelpScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/help2.png");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
}

//�X�V����
eSceneType HelpScene::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//�`�揈��
void HelpScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(32);
	DrawString(20, 120, "�w���v���", 0xffff00, 0);

	SetFontSize(16);
	DrawString(20, 160, "����͖W�Q���ƃv���C���[����", 0xffffff, 0);
	DrawString(20, 180, "������Đ키�ΐ�^�Q�[���ł��B", 0xffffff, 0);
	DrawString(20, 220, "�W�Q���͊e�{�^���ɐݒ肳�ꂽ", 0xffffff, 0);
	DrawString(20, 240, "�W�Q��i�Ńv���C���[��W�Q��", 0xffffff, 0);
	DrawString(20, 260, "�v���C���[��HP��0�ɂ��邱�Ƃŏ����B", 0xffffff, 0);
	DrawString(20, 300, "�v���C���[����HP��0�ɂȂ�܂ł�", 0xffffff, 0);
	DrawString(20, 320, "��萔�ȏ�̃X�R�A���l�����邱�Ƃŏ���,", 0xffffff, 0);

	DrawBoxAA(10, 445, 370, 470, 0x00ff00, TRUE);
	DrawString(20, 450, "----	B�{�^���������ă^�C�g���֖߂�	----", 0xff0000, 0);
}

//�I��������
void HelpScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
}

//���݂̃V�[�������擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}