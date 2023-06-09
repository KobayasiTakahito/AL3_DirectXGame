﻿#include "Player.h"
#include "Enemy.h"
#include <cassert>
#include<world.h>
#include "ImGuiManager.h"


void Player::Initialize(Model* model, uint32_t &textureHandle) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	texturehandle_ = textureHandle;
	worldTransform_.Initialize();
	//シングルインスタンスを取得する
	input_ = Input::GetInstance();

	
}


	
// 更新
void Player::Update() {
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//行列指定バッファ
	worldTransform_.UpdateMatrix();

	//キャラクターの移動速度
	const float kChracterSpeed = 0.3f;
	//移動限界
	const float kMoveLimiX = 30.0f;
	const float kMoveLimiY = 18.0f;


	float imputFloat3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	// デバッグ
	ImGui::Begin("Debug");
	ImGui::SliderFloat3("player", imputFloat3, -30.0f, 30.0f);
	ImGui::End();
	worldTransform_.translation_.x = imputFloat3[0];
	worldTransform_.translation_.y = imputFloat3[1];
	worldTransform_.translation_.z = imputFloat3[2];

	//押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kChracterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kChracterSpeed;
	}
	//押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_UP)) {
		move.y -= kChracterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y += kChracterSpeed;
	}
	//
	Player::Rotate();

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimiX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimiX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimiY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimiY);


	//座標ベクトルの加算
	worldTransform_.translation_ = Vec3Add(worldTransform_.translation_,move);
	
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);
	
	Player::Attack();
	

	if (bullet_) {
		bullet_->Update();
	}
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	

}

//旋回
void Player::Rotate() { 
	//回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;
	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

//デストラクタ
Player::~Player() { 
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
		bullet = nullptr;
	}
}

//攻撃
void Player::Attack() { 
	if (input_->PushKey(DIK_SPACE)) {
		/*if (bullet_) {
			delete bullet_;
			bullet_ = nullptr;
		}*/
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 Velocity(0, 0, kBulletSpeed);

		Velocity = TransformNormal(Velocity, worldTransform_.matWorld_);

	//弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_,Velocity);
		// 弾を登録する
		bullets_.push_back(newBullet);

		bullet_ = newBullet;
	}
	
}

// 描画
void Player::Draw(ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection, texturehandle_);
	if (bullet_) {
		//bullet_->Draw(viewprojection);
		for (PlayerBullet* bullet : bullets_) {
			bullet->Draw(viewprojection);
		}
	}
	
	
}

//ワールド座標を入れる変数
Vector3 Player::GetWorldPos() {

	Vector3 worldPos;

	worldPos.x = player_->worldTransform_.translation_.x;
	worldPos.y = player_->worldTransform_.translation_.y;
	worldPos.z = player_->worldTransform_.translation_.z;

	return worldPos;
}
