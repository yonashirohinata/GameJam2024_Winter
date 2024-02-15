#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

#define MAX_FUEL 20000
#define MAX_HP 100

struct Bright
{
	int red;
	int green;
	int blue;
};
class Player
{
private:
	bool is_active;			//有効状態か？
	int image;				//画像データ
	Vector2D location;		//位置座標
	Vector2D box_size;		//当たり判定の大きさ
	float angle;			//角度
	float speed;			//速さ
	float hp;				//体力
	float fuel;				//燃料
	int alpha_flg;			//透明度は有効か？
	bool vanish_flg;		//透明になったか？
	int vanish_timer;		//透明化の時間
	int player_alpha;		//プレイヤーの透明度
	int barrier_count;		//バリアの枚数
	Barrier* barrier;		//バリア
	Bright bright;			//明るさ調整用
	
public:
	Player();
	~Player();

	void Initialize();		//初期化処理
	void Update();			//更新処理
	void Draw();			//描画処理
	void Finalize();		//終了時処理

public:
	void SetActive(bool flg);			//有効フラグ設定
	void ControlHp(float value);		//体力減少処理
	void ControlFuel(float value);		//燃料管理処理
	Vector2D GetLocation() const;		//位置座標取得
	Vector2D GetBoxSize() const;		//当たり判定の大きさ取得
	float GetSpeed() const;				//速さ取得処理
	float GetFuel() const;				//燃料取得
	float GetHp() const;				//体力取得
	int GetBarrierCount()  const;		//バリアの枚数取得
	bool IsBarrier()  const;			//バリア有効か？を取得
	int IsVanish();						//透明化が有効か？を取得
	void Acceleration();				//加速処理
	
private:
	void Movement();			//移動処理
	void Vanishment();			//透明化処理
	void Damage();				//ダメージ処理
};