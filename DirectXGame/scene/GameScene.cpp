#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete player_;
	for (Enemy* enemy : enemy_) {
		delete enemy;
	}
	delete model_;
	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
	delete railCamera_;
}

void GameScene::Initialize() {
	loadEnemyPopData();
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
	model2_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("tama", true);
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	Vector3 playerPos(0, 0, 30);
	//レティクルのテクスチャ
	TextureManager::Load("reticle.png");
	player_->Initialize(model_,model2_,textureHandle_,playerPos);
	
	enemyPop(Vector3(0.0f,0.0f,5.0f));
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1270, 820);
	//軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	
	//背景
	skydome_ = new Skydome();
	skydome_->Initializa(modelSkydome_);
	//レールカメラ
	railCamera_ = new RailCamera();
	railCamera_->Initializ(worldTransform_.translation_,worldTransform_.rotation_);
	player_->SetParent(&railCamera_->GetWorldTransform());
}

void GameScene::Update() {
	railCamera_->Update();
	player_->Update(viewProjection_);
	skydome_->Update();
	updateEnemyPopCommands();
	CheckAllColision();
	enemy_.remove_if([](Enemy* enemy) { 
		if (enemy->IsDead()) {
		delete enemy;
			return true;
		}
		return false;
	});

	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	for (Enemy* enemy : enemy_) {
		enemy->Update();
		
	}
	for (EnemyBullet* bullet : bullets_) {

		bullet->Update();
		
	}

	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0)) {
		isDebugcameraActive_ = !isDebugcameraActive_;

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
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = GetBullets();

	#pragma region
	posA = player_->GetWorldPos();

	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();
		if (pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z), 2) <=pow(3, 2)) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
	for (Enemy* enemy : enemy_) {
		posB = enemy->GetWorldPosition();
		for (PlayerBullet* bullet : playerBullets) {
			posA = bullet->GetWorldPosition();
			if (pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z), 2) <=
			    pow(3, 2)) {
				bullet->OnCollision();
				enemy->OnCollision();
			}
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
	for (Enemy* enemy : enemy_) {
		
		enemy->Draw(viewProjection_);
	}
	
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
	player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	//リストに追加	
	bullets_.push_back(enemyBullet);
}

void GameScene::enemyPop(Vector3 vec) {
	//// 敵キャラ
	const float kEnemySpeed = -0.02f;
	Vector3 Velocity(0, 0, kEnemySpeed);
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(model_, Vec3Add(worldTransform_.translation_, vec), Velocity);
	enemy_.push_back(newEnemy);
	for (Enemy* enemy : enemy_) {
		enemy->SetPlayer(player_);
		enemy->SetGameScene(this);
	}
}

void GameScene::loadEnemyPopData() { 
	std::ifstream file;
	file.open("ENEMY.csv");
	assert(file.is_open());
	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();
	//ファイルを閉じる
	file.close();
	
}
void GameScene::updateEnemyPopCommands() {
	//待機処理
	if (stopF) {
		timer--;
		if (timer <= 0) {
			stopF = false;
		}
		return;
	}
	
	//1行文の文字列を入れる変数
	std::string line;
	
	//コマンド実行ループ
	while (std::getline(enemyPopCommands,line)) {
		//１行枌尾文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		
		std::string word;
		//,区切りで行の先頭文字列を取得
		std::getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			continue;
		}
		//POPコマンド
		if (word.find("POP") == 0) {
		 std::getline(line_stream, word, ',');
		float x = (float)std::atof(word.c_str());
		 
		std::getline(line_stream, word, ',');
		 float y = (float)std::atof(word.c_str());

		  std::getline(line_stream, word, ',');
		 float z = (float)std::atof(word.c_str());
		
		 //敵を発生させる
		 enemyPop(Vector3(x, y, z));
		} else if (word.find("WAIT") == 0) {
		 std::getline(line_stream, word, ',');

		 //待ち時間
		 int32_t waitTime = atoi(word.c_str());

		 //待機開始
		 stopF = true;
		 timer = waitTime;

		 break;
		}

	}
	
}

void GameScene::AddEnemy(Enemy* enemy) { enemy_.push_back(enemy); }