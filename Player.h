﻿#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"
#include "PlayerBullet.h"

class Player {
public:
	//初期化
	void Initialize(Model* model,uint32_t &textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection &viewprojection);

	//旋回
	void Rotate();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();



private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t texturehandle_ = 0u;
	//自キャラ
	Player* player_ = nullptr;
	//キーボード入植
	Input* input_ = nullptr;
	//弾
	PlayerBullet* bullet_ = nullptr;
	
};
