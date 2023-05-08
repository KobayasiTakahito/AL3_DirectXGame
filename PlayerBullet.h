﻿#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"
#include "Vector3.h"

class PlayerBullet {
public:
	///初期化
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	private:

		// ワールド変換データ
	    WorldTransform worldTransform_;
	    // モデル
	    Model* model_ = nullptr;
	    // テクスチャハンドル
	    uint32_t texturehandle_ = 0u;
};
