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

class Enemy {
public:
	/// 初期化
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Fire();

	void Firetime();


	// 弾
	std::list<EnemyBullet*> bullets_;
	static const int kFireInterval = 60;

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
	// 弾
	EnemyBullet* bullet_ = nullptr;
	//発射タイマー
	int32_t FireTimer_ = 0;

};

