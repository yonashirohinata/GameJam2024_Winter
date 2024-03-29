#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Object/Item.h"
#include "../Object/Cheak.h"

struct SpeedUp
{
	float x;
	float y;
};
class GameMainScene : public SceneBase
{
private:
	int high_score;			//ハイスコア
	int back_ground;		//背景画像
	int barrier_image;		//バリア画像
	int car_engine_image;	//加速アイテム画像
	int oil_tank_image;		//燃料アイテム画像
	int tool_box_image;		//HP回復アイテム画像
	int speed_up_image;		//スピードアップ時の演出画像
	int mileage;			//走行距離
	int enemy_image[3];		//敵画像
	int enemy_count[3];		//通りすぎた敵カウント
	int item_image[3];
	int item_count[3];
	
	int main_bgm;
	int heal_se;
	int damage_se;

	int cut_in;
	int cut_time;
	Player* player;			//プレイヤー
	Enemy** enemy;			//敵
	Item** item;             //アイテム
	Cheak* cheak[5];			//判定

	SpeedUp speed_direction;

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

	void Recover();

	//当たり判定
	bool IsHitCheck(Player* p, Enemy* e);

	bool IsHitCheck2(Player* p, Cheak* c);
	bool IsHitCheck_item(Player* p, Item* i);
};