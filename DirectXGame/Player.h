#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"
#include "PlayerBullet.h"
#include <list>
#include "Enemy.h"
#include "Sprite.h"

class Player {
public:
	//初期化
	void Initialize(Model* model, Model* model2, uint32_t& textureHandle, Vector3 pos);

	//更新
	void Update(const ViewProjection viewporjection);

	//描画
	void Draw(ViewProjection &viewprojection);

	//旋回
	void Rotate();
	//デストラクタ
	~Player();
	//ワールド座標を入れる変数
	Vector3 GetWorldPos();
	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	//弾
	std::list<PlayerBullet*> bullets_;
	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();


private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//３Ｄレティクル用
	WorldTransform worldTransform3DReticle_;
	//２Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr; 
	//モデル
	Model* model_ = nullptr;
	Model* model2_ = nullptr;
	//テクスチャハンドル
	uint32_t texturehandle_ = 0u;
	//自キャラ
	
	//キーボード入植
	Input* input_ = nullptr;
	//弾
	PlayerBullet* bullet_ = nullptr;
	int fireTime_ = 0;
	//敵
	Enemy* enemy_ = nullptr;
	
};
