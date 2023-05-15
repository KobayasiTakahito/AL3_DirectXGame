#include "Enemy.h"
#include <assert.h>
#include "Vector3.h"
#include "world.h"


void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	// テクスチャ読み込む
	texturehandle_ = TextureManager::Load("enemy.png");
	Vector3 tmp = {0,5,100};
	// ワールドトランスフォーの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vec3Add(Vec3Add(worldTransform_.translation_, position),tmp);
	worldTransform_.UpdateMatrix();

	velocity_ = velocity;

}
void Enemy::Update() {
	Vector3 velocity = {1, 1, 0};
	switch (phase_) {
	case Phase::Approch:
		worldTransform_.translation_ = Vec3Add(worldTransform_.translation_, velocity_);
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:

		worldTransform_.translation_ = Vec3Add(worldTransform_.translation_, velocity);

		break;
	
	}
	worldTransform_.UpdateMatrix();
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, texturehandle_);
}