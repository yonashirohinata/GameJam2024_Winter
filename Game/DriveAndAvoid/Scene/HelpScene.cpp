#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//初期化処理
void HelpScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/help2.png");

	//
	select_se = LoadSoundMem("Resource/sounds/決定ボタンを押す23.mp3");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (select_se == -1)
	{
		throw("Resource/sounds/決定ボタンを押す22.mp3がありません\n");
	}
}

//更新処理
eSceneType HelpScene::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(select_se, DX_PLAYTYPE_BACK, TRUE);

		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//描画処理
void HelpScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(32);
	DrawString(20, 120, "ヘルプ画面", 0xffff00, 0);

	SetFontSize(16);
	DrawString(20, 160, "これは妨害側とプレイヤー側に", 0xffffff, 0);
	DrawString(20, 180, "分かれて戦う対戦型ゲームです。", 0xffffff, 0);
	DrawString(20, 220, "妨害側は各ボタンに設定された", 0xffffff, 0);
	DrawString(20, 240, "妨害手段でプレイヤーを妨害し", 0xffffff, 0);
	DrawString(20, 260, "プレイヤーのHPを0にすることで勝利。", 0xffffff, 0);
	DrawString(20, 300, "プレイヤー側はHPが0になるまでに", 0xffffff, 0);
	DrawString(20, 320, "一定数以上のスコアを獲得することで勝利,", 0xffffff, 0);

	DrawBoxAA(10, 445, 370, 470, 0x00ff00, TRUE);
	DrawString(20, 450, "----	Bボタンを押してタイトルへ戻る	----", 0xff0000, 0);
}

//終了時処理
void HelpScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報を取得
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}