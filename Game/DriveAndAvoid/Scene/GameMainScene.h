#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Object/Item.h"

class GameMainScene : public SceneBase
{
private:
	int high_score;			//ハイスコア
	int back_ground;		//背景画像
	int barrier_image;		//バリア画像
	int car_engine_image;
	int oil_tank_image;
	int tool_box_image;
	int mileage;			//走行距離
	int enemy_image[3];		//敵画像
	int enemy_count[3];		//通りすぎた敵カウント
	int item_image[3];
	int item_count[3];
	Player* player;			//プレイヤー
	Enemy** enemy;			//敵
	Item** item;             //アイテム

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//ハイスコア読み込み処理
	void ReadHighScore();

	//当たり判定
	bool IsHitCheck(Player* p, Enemy* e);
	bool IsHitCheck_item(Player* p, Item* i);
};