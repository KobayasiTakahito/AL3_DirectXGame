#include "Enemy.h"
#include <assert.h>
#include "Vector3.h"
#include "world.h"
#include"Player.h"


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
	Vector3 velocity = {0.0f, 0.0f, 0.0f};
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
	
	Enemy::Firetime();

	
	
	}

// 攻撃
    void Enemy::Fire() {
	assert(player_);
		
		// 弾の速度
		const float kBulletSpeed = -0.01f;
	Vector3 playerVec = player_->GetWorldPos();
	Vector3 enemyVec = GetWorldPosition();
	Vector3 c = Vec3Sub(playerVec, enemyVec);
	c = Vec3Normalize(c);

		Vector3 Velocity(Vec3Add(c,{0.0f,0.0f,kBulletSpeed}));
		Velocity = TransformNormal(Velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化
	    EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, Velocity);
		

		
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
	    
		
}

Vector3 Enemy::GetWorldPosition() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform_.translation_.x;
	    worldPos.y = worldTransform_.translation_.y;
	    worldPos.z = worldTransform_.translation_.z;

	    return worldPos;
}
// 衝突を検出したら呼び出されるコールバック関数
void Enemy::OnCollision() {

}
