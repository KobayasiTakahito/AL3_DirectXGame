﻿#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"
#include <list>
#include "Vector3.h"

class EnergyPack {
public:
	/// 初期化
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t texturehandle_ = 0u;

	Vector3 velocity_;

	int healNum_;
	// 寿命
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t dethTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
};