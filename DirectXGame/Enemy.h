#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"
#include <list>
#include "Vector3.h"
#include "EnemyBullet.h"


enum class Phase {
	Approch,
	Leave,
};

class Player;

class GameScene;

class Enemy {
public:
	/// 初期化
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Fire();

	void Firetime();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	static const int kFireInterval = 60;

	bool IsDead() const { return isDead_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t texturehandle_ = 0u;
	Vector3 velocity_;
	//フェーズ
	Phase phase_ = Phase::Approch;
	
	//発射タイマー
	int32_t FireTimer_ = 0;

	//デスフラグ
	bool isDead_ = false;

	//自キャラ
	Player* player_ = nullptr;
	//ゲームシーン
	GameScene* gameScene_ = nullptr; 

};

