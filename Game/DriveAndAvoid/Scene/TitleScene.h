#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
private:

private:
	int background_image;		//�w�i�摜
	int start_image;			//�X�^�[�g�{�^���摜
	int help_image;				//�w���v�{�^���摜
	int end_image;				//�G���h�{�^���摜
	int start_select_image;		//�X�^�[�g�I���{�^���摜
	int help_select_image;		//�w���v�I���{�^���摜
	int end_select_image;		//�G���h�I���{�^���摜
	int cursor_image;			//�J�[�\���摜
	int menu_cursor;			//�J�[�\��

	int title_bgm;				//�^�C�g��BG�l
	int choose_se;				//�I��SE
	int select_se;				//����SE

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};