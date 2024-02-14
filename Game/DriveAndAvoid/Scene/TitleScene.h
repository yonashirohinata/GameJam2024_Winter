#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
private:

private:
	int background_image;		//
	int menu_image;				//
	int start_image;			//�X�^�[�g�I���{�^���摜
	int help_image;				//�w���v�I���{�^���摜
	int end_image;				//�G���h�I���{�^���摜
	int location_y;				//Y���W�擾
	int move_y;					//�㉺�ړ�
	int cursor_image;			//
	int menu_cursor;			//

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};