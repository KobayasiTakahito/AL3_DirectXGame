#include "PlayerBullet.h"
#include <assert.h>
#include "Vector3.h"


void PlayerBullet::Initialize(Model* model, const Vector3& position) { 
	//NULLポインタチェック
	assert(model);
	model_ = model;
	
	//テクスチャ読み込む
	texturehandle_ = TextureManager::Load("block.png");

	//ワールドトランスフォーの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = Vec3Add(worldTransform_.translation_, position);
	worldTransform_.UpdateMatrix();
}
void PlayerBullet::Update() {

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, texturehandle_);
}
