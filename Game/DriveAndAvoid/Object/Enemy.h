#pragma once

#include "../Utility/Vector2D.h"
#include "../Object/Player.h"

class Enemy
{
private:
	int type;				//タイプ
	int image;				//画像
	int damage;				//画像
	int Note;			//注意時の画像
	int	Dangerous;			//危ない時の画像
	int lane1, lane2, lane3, lane4, lane5;     //レーンの場所
	float speed;			//速さ
	Vector2D location;		//位置情報
	Vector2D location1;		//位置情報
	Vector2D location2;		//位置情報
	Vector2D location3;		//位置情報
	Vector2D location4;		//位置情報
	Vector2D location5;		//位置情報
	Vector2D box_size;		//当たり判定の大きさ
	Vector2D No_box_size;		//当たり判定の大きさ
	int cursor;				//カーソルの選択
	int time;				//待機時間
	
	bool attackflg;			//ダメージ範囲内にいるか（１レーンのみ）
	bool attackflg2;		//ダメージ範囲内にいるか（３レーン）
	int Damage;
public:
	bool flg;				//フラグ（false.オフ、true.オン）
	Enemy(int type, int handle);
	~Enemy();

	void Initialize();				//初期化処理
	void Update(float speed);		//更新処理
	void Draw() const;				//描画処理
	void Finalize();				//終了時処理

	int GetType() const;				//タイプの取得
	Vector2D GetLocation() const;		//位置情報の取得
	Vector2D GetBoxSize() const;		//当たり判定の大きさを取得
	void Timer();			//当たらないところにいるかを取得
	void Cheaklane();		//レーンの番号を判定
private:
	void Movement();			//移動処理
	void WeakTarget();				//ターゲット場所指定（小）
	void StrongTarget();				//ターゲット場所指定（大）

};
