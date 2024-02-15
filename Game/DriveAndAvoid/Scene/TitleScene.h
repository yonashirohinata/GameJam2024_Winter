#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
private:

private:
	int background_image;		//背景画像
	int start_image;			//スタートボタン画像
	int help_image;				//ヘルプボタン画像
	int end_image;				//エンドボタン画像
	int start_select_image;		//スタート選択ボタン画像
	int help_select_image;		//ヘルプ選択ボタン画像
	int end_select_image;		//エンド選択ボタン画像
	int cursor_image;			//カーソル画像
	int menu_cursor;			//カーソル

	int title_bgm;				//タイトルBGＭ
	int choose_se;				//選択SE
	int select_se;				//決定SE

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};