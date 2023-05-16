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
		/*if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}*/
		break;
	case Phase::Leave:

		worldTransform_.translation_ = Vec3Add(worldTransform_.translation_, velocity);

		break;
	
	}

	worldTransform_.UpdateMatrix();
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	Enemy::Firetime();

	if (bullet_) {
		bullet_->Update();
	}
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	

	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	}

// 攻撃
    void Enemy::Fire() {
	
		/*if (bullet_) {
		    delete bullet_;
		    bullet_ = nullptr;
		}*/
		// 弾の速度
		const float kBulletSpeed = -2.0f;
		Vector3 Velocity(0, 0, kBulletSpeed);

		Velocity = TransformNormal(Velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化
	    EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, Velocity);
		// 弾を登録する
		bullets_.push_back(newBullet);

		bullet_ = newBullet;
	}
    
	void Enemy::Firetime() {
	    FireTimer_--;
	    if (FireTimer_ <= 0) {
		Fire();
		FireTimer_ = kFireInterval;
	    }
    }


void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, texturehandle_);
	    if (bullet_) {
		// bullet_->Draw(viewprojection);
		for (EnemyBullet* bullet : bullets_) {
			bullet->Draw(viewProjection);
		}
	    }
}