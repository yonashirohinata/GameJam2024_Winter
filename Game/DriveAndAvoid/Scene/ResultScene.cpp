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

//初期化処理
void ResultScene::Initialize()
{
	//画像の読み込み
	back_ground = LoadGraph("Resource/images/back.bmp");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);

	player_win_se = LoadSoundMem("Resource/sounds/ドンドンパフパフ.mp3");

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmpがありません\n");
	}
	if (player_win_se == -1)
	{
		throw("Resource/sounds/ドンドンパフパフ.mp3がありません\n");
	}

	//ゲーム結果の読み込み
	ReadResultData();

	PlaySoundMem(player_win_se, DX_PLAYTYPE_BACK, TRUE);

}

//更新処理
eSceneType ResultScene::Update()
{
	//Bボタンでランキングに遷移する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//描画処理
void ResultScene::Draw() const
{
	//背景画像を描画
	DrawGraph(0, 0, back_ground, TRUE);

	//スコア等表示領域
	DrawBox(150, 150, 490, 330, GetColor(0, 153, 0), TRUE);
	DrawBox(150, 150, 490, 330, GetColor(0, 0, 0), FALSE);

	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);

	SetFontSize(32);
	if ((hp <= 0.0f || fuel <= 0.0f) && score / 10 < 3500)
	{
		DrawString(200, 160, "プレイヤー2WIN", GetColor(204, 0, 0));
	}
	else if((hp <= 0.0f || fuel <= 0.0f) && score / 10 >= 3500)
	{
		DrawString(200, 160, "プレイヤー1WIN", GetColor(204, 0, 0));
	}
	//↓if文で表示させる妨害側のやつ
	//if(設定された基準値 > score || player->GetHp() < 0.0f)
	//DrawString(200, 160, "妨害側WIN", GetColor(204, 0, 0));
	SetFontSize(16);
	//DrawString(180, 200, "走行距離     ", GetColor(0, 0, 0));
	//for (int i = 0; i < 3; i++)
	//{
	//	DrawRotaGraph(230, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[i], TRUE);
	//	DrawFormatString(260, 220 + (i * 21), GetColor(255, 255, 255), "%6d x %4d=%6d", enemy_count[i], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);
	//}
	SetFontSize(32);
	DrawString(180, 240, "走行距離", GetColor(0, 0, 0));

	DrawFormatString(180, 240, 0xFFFFFF, "         =%6d", score / 10);

}

//終了時処理
void ResultScene::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}
}

//現在のシーン情報を取得
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

//リザルトデータの読み込み
void ResultScene::ReadResultData()
{
	//ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_date.csvが読み込めません\n");
	}


	//結果を読み込む
	fscanf_s(fp, "%6d,\n", &score);

	//避けた数と得点を取得
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%6d,\n", &enemy_count[i]);
	}

	fscanf_s(fp, "%d,\n", &fuel);
	fscanf_s(fp, "%d,\n", &hp);
	fscanf_s(fp, "%d,\n", &mileage);

	//ファイルクローズ
	fclose(fp);
}