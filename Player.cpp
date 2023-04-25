#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t &textureHandle) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	texturehandle_ = textureHandle;
	worldTransform_.Initialize();
}
   
// 更新
void Player::Update() {}

// 描画
void Player::Draw(ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection, texturehandle_);
}
