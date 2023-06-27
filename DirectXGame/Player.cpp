#include "Player.h"
#include "Enemy.h"
#include <cassert>
#include<world.h>
#include "ImGuiManager.h"
#include "Sprite.h"


void Player::Initialize(Model* model, Model* model2, uint32_t& textureHandle, Vector3 pos) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	model2_ = model2;
	texturehandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform3DReticle_.Initialize();
	//シングルインスタンスを取得する
	input_ = Input::GetInstance();
	worldTransform_.translation_ = Vec3Add(worldTransform_.translation_, pos);
	//レティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("reticle.png");
	sprite2DReticle_ = Sprite::Create(
	    textureReticle,
	    Vector2(worldTransform_.translation_.x + pos.x, worldTransform_.translation_.y + pos.y),
	    Vector4(1.0f, 1.0f, 1.0f, 1.0f),
	    Vector2(0.5f, 0.5f));
	
	
}


	
// 更新
void Player::Update(const ViewProjection viewporjection) {
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	

	//キャラクターの移動速度
	const float kChracterSpeed = 0.3f;
	//移動限界
	const float kMoveLimiX = 30.0f;
	const float kMoveLimiY = 18.0f;


	float imputFloat3[3] = {
	    worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1],
	    worldTransform_.matWorld_.m[3][2]};
	float worldReticle[3] = {
	    worldTransform3DReticle_.matWorld_.m[3][0], worldTransform3DReticle_.matWorld_.m[3][1],
	    worldTransform3DReticle_.matWorld_.m[3][2]};
	// デバッグ
	ImGui::Begin("Debug");
	ImGui::SliderFloat3("player", imputFloat3, -30.0f, 30.0f);
	ImGui::SliderFloat3("Reticle", worldReticle, -30.0f, 30.0f);
	ImGui::End();
	worldTransform_.matWorld_.m[3][0] = imputFloat3[0];
	worldTransform_.matWorld_.m[3][1] = imputFloat3[1];
	worldTransform_.matWorld_.m[3][2] = imputFloat3[2];
	worldTransform3DReticle_.matWorld_.m[3][0] = imputFloat3[0];
	worldTransform3DReticle_.matWorld_.m[3][1] = imputFloat3[1];
	worldTransform3DReticle_.matWorld_.m[3][2] = imputFloat3[2];

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
	
	
	// 行列指定バッファ
	worldTransform_.UpdateMatrix();

	Player::Attack();
	

	if (bullet_) {
		bullet_->Update();
	}
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	//自機のワールド座標から３Dレティクルのワールド座標を計算
	const float kDistancePlayerTo3DReticle = 50.0f;
	//自機から３Dレティクルへのオフセット（ｚ＋向き）
	Vector3 offest = {0, 0, 1.0f};
	//自機のワールド行列の回転を反映
	offest = TransformNormal(offest, worldTransform_.matWorld_);
	//ベクトルの長さを変える
	offest = Multiply(kDistancePlayerTo3DReticle, Normalise(offest));
	Vector3 n = GetWorldPos();
	//３Ｄレティクルの座標を設定
	worldTransform3DReticle_.translation_ = Vec3Add(GetWorldPos(), offest);
	worldTransform3DReticle_.UpdateMatrix();
	//3Dレティクルのワールド座標から２Dレティクルのスクリーン座標を計算
	Vector3 positionReticle = worldTransform3DReticle_.translation_;
	//ビューポート行列
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	//ビュー行列とプロジェクション行列、ビューポート行列を合成
	Matrix4x4 matViewProjectionViewport =
	    Multiply(Multiply(viewporjection.matView, viewporjection.matProjection), matViewport);
	positionReticle = Transform(positionReticle, matViewProjectionViewport);
	

	POINT mousePosition;
	//マウス座標（スクリーン座標）を取得する
	GetCursorPos(&mousePosition);

	//クライアントエリア座標（スクリーン座標）に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	sprite2DReticle_->SetPosition(Vector2(float(mousePosition.x), float (mousePosition.y)));
	//ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPV =
	    Multiply(Multiply(viewporjection.matView, viewporjection.matProjection), matViewport);
	//合成行列の逆行列を計算
	Matrix4x4 matInverseVPV = Inverse(matVPV);

	//スクリーン座標
	Vector3 posNear = Vector3(float(mousePosition.x), float(mousePosition.y), 0);
	Vector3 posFar = Vector3(float(mousePosition.x), float(mousePosition.y), 1);

	//スクリーン座標系からワールド座標系へ
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	//マウスレイの方向
	Vector3 mouseDirection = Vec3Sub(posFar, posNear);
	mouseDirection = Normalise(mouseDirection);

	//カメラから照準オブジェクトの距離
	const float kDistanceTestObject = 30;
	worldTransform3DReticle_.translation_ = Multiply(kDistanceTestObject, mouseDirection);

	worldTransform3DReticle_.UpdateMatrix();
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
	delete sprite2DReticle_;
}

//攻撃
void Player::Attack() { 
	if (input_->PushKey(DIK_SPACE)) {
	
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 Velocity(0, 0, kBulletSpeed);
		Velocity = Vec3Sub(worldTransform3DReticle_.translation_, worldTransform_.translation_);

		Velocity = Multiply(kBulletSpeed,Vec3Normalize(Velocity));

	//弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		
		newBullet->Initialize(model_, GetWorldPos(), Velocity);
		// 弾を登録する
		bullets_.push_back(newBullet);

		bullet_ = newBullet;
	}
	
}

// 描画
void Player::Draw(ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection, texturehandle_);
	model2_->Draw(worldTransform3DReticle_, viewprojection,texturehandle_);
	
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

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
// 衝突を検出したら呼び出されるコールバック関数
void Player::OnCollision() {

}

void Player::DrawUI() { 
	sprite2DReticle_->Draw();
}

void Player::SetParent(const WorldTransform* parent){ worldTransform_.parent_ = parent; }