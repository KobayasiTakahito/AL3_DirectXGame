#include "Player.h"
#include <cassert>
#include<world.h>

void Player::Initialize(Model* model, uint32_t &textureHandle) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	texturehandle_ = textureHandle;
	worldTransform_.Initialize();
	//シングルインスタンスを取得する
	input_ = Input::GetInstance();
}
  
Vector3 Player::Vec3Add(Vector3 add1, Vector3 add2) {
	Vector3 add3;
	add3.x = add1.x + add2.x;
	add3.y = add1.y + add2.y;
	add3.z = add1.z + add2.z;
	return add3;
}

	
// 更新
void Player::Update() {
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	//キャラクターの移動速度
	const float kChracterSpeed = 5.0f;
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
	//座標ベクトルの加算
	worldTransform_.translation_ = Vec3Add(worldTransform_.translation_,move);
	/*worldTransform_.scale_;
	worldTransform_.rotation_;
	worldTransform_.translation_ = MakeTranslateMatrix()*/

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);
	
}


// 描画
void Player::Draw(ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection, texturehandle_);
}
