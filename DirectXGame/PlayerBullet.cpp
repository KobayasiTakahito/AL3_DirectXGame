#include "PlayerBullet.h"
#include <assert.h>
#include "Vector3.h"
#include "world.h"
#include "Player.h"


void PlayerBullet::Initialize(Model* model, const Vector3& position ,const Vector3& velocity) { 
	//NULLポインタチェック
	assert(model);
	model_ = model;
	
	//テクスチャ読み込む
	texturehandle_ = TextureManager::Load("block.png");

	//ワールドトランスフォーの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vec3Add(worldTransform_.translation_, position);
	worldTransform_.UpdateMatrix();

	velocity_ = velocity;
}
void PlayerBullet::Update() {
	
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Vec3Add(worldTransform_.translation_, velocity_);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
	//時間経過でデス
	if (--dethTimer_ <= 0) {
		isDead_ = true;
	}

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	
	model_->Draw(worldTransform_, viewProjection, texturehandle_);
}
// 衝突を検出したら呼び出されるコールバック関数
void PlayerBullet::OnCollision() { 
	isDead_ = true;
}
