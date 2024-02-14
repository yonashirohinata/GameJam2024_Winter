#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : background_image(NULL), menu_image(NULL), start_image(NULL), help_image(NULL), end_image(NULL), cursor_image(NULL), menu_cursor(0), location_y(0), move_y(0)
{
	
}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/Title.bmp");
	menu_image = LoadGraph("Resource/images/menu.bmp");
	start_image = LoadGraph("Resource/images/start_m.bmp");
	help_image = LoadGraph("Resource/images/help_m.bmp");
	end_image = LoadGraph("Resource/images/end_m.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}
	if (start_image == -1)
	{
		throw("Resource/images/start_m.bmpがありません\n");
	}
	if (help_image == -1)
	{
		throw("Resource/images/help_m.bmpがありません\n");
	}
	if (end_image == -1)
	{
		throw("Resource/images/end_m.bmpがありません\n");
	}
}

//更新処理
eSceneType TitleScene::Update()
{
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN)|| InputControl::GetButtonDown2(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//1番下に到達したら、一番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP) || InputControl::GetButtonDown2(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//1番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	//カーソルY座標位置情報取得
	location_y += 40 * menu_cursor;

	//カーソル決定（決定した画面に遷移する）
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

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	//タイトル画面の描画
	DrawGraph(0, 0, background_image, FALSE);

	//メニュー画像の描画
	//DrawGraph(120, 200, menu_image, TRUE);

	//スタートボタン画像の描画
	if (menu_cursor == 0)
	{
		DrawGraph(120, location_y, start_image, TRUE);

	}
	else
	{
		DrawGraph(120, 200, start_image, TRUE);
	}

	//ヘルプボタン画像の描画
	DrawGraph(101, 280, help_image, TRUE);
	
	//エンドボタン画像の描画
	DrawGraph(80, 320, end_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}