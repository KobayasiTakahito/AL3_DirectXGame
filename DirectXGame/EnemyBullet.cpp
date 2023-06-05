#include "EnemyBullet.h"
#include "PlayerBullet.h"
#include <assert.h>
#include "Vector3.h"
#include "world.h"


void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	// テクスチャ読み込む
	texturehandle_ = TextureManager::Load("block.png");

	// ワールドトランスフォーの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vec3Add(worldTransform_.translation_, position);
	worldTransform_.UpdateMatrix();

	velocity_ = velocity;
}
void EnemyBullet::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Vec3Add(worldTransform_.translation_, velocity_);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 時間経過でデス
	if (--dethTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	
		model_->Draw(worldTransform_, viewProjection, texturehandle_);
	
}
void EnemyBullet::OnCollision() { 
	isDead_ = true; 
}

Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}