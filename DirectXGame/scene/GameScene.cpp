#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete player_;
	delete enemy_;
	delete model_;
	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
	delete railCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロダクションの初期化
	viewProjection_.Initialize();
	//3Dモデルの生成
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("tama", true);
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	Vector3 playerPos(0, 0, 50);
	player_->Initialize(model_,textureHandle_,playerPos);
	
	
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1270, 820);
	//軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//// 敵キャラ
	const float kEnemySpeed = -0.1f;
	Vector3 Velocity(0, 0, kEnemySpeed);
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(model_, worldTransform_.translation_, Velocity);
	enemy_ = newEnemy;
	enemy_->SetPlayer(player_);
	enemy_->SetGameScene(this);
	//背景
	skydome_ = new Skydome();
	skydome_->Initializa(modelSkydome_);
	//レールカメラ
	railCamera_ = new RailCamera();
	railCamera_->Initializ(worldTransform_.translation_,worldTransform_.rotation_);
	player_->SetParent(&railCamera_->GetWorldTransform());
}

void GameScene::Update() {
	skydome_->Update();
	railCamera_->Update();
	player_->Update();
	enemy_->Update();

	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0)) {
		isDebugcameraActive_ = true;
	}

#endif // DEBUG
	//カメラの処理
	if (isDebugcameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		// レールカメラ
		viewProjection_.UpdateMatrix();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}

}

void GameScene::CheckAllColision() { 
	//判定対象AとBの座標
	Vector3 posA, posB;

	//自弾リストの取得
	//const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = GetBullets();

	#pragma region
	posA = player_->GetWorldPos();

	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();
		if (pow((posB.x - posA.x), 2) + pow((posB.y - posA.x), 2) + pow((posB.z - posA.z), 2) >=pow(2, 2)) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region
    #pragma endregion

	#pragma region
    #pragma endregion

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>



	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	skydome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	
	enemy_->Draw(viewProjection_);
	for (EnemyBullet* bullet : bullets_) {

		bullet->Draw(viewProjection_);
	}

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	//リストに追加	
	bullets_.push_back(enemyBullet);
}