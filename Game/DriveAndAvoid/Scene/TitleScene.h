#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
private:

private:
	int background_image;		//
	int menu_image;				//
	int start_image;			//スタート選択ボタン画像
	int help_image;				//ヘルプ選択ボタン画像
	int end_image;				//エンド選択ボタン画像
	int location_y;				//Y座標取得
	int move_y;					//上下移動
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