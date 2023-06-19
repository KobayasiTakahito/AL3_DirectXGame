#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"
#include <sstream>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>

	void CheckAllColision();

	/// <summary>
	/// 敵弾を追加
	/// </summary>

	void AddEnemyBullet(EnemyBullet* enemyBullet);
	const std::list<EnemyBullet*>& GetBullets() { return bullets_; }

	
	/// <summary>
	/// 敵を追加
	/// </summary>
	void AddEnemy(Enemy* enemy);
	void enemyPop(Vector3 vec);



	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void loadEnemyPopData();
	/// <summary>
	/// 敵発生データの更新
	/// </summary>
	void updateEnemyPopCommands();



private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロダクションの初期化
	ViewProjection viewProjection_;
	//３Dモデル
	Model* model_ = nullptr;
	Model* model2_ = nullptr;
	//デバッグカメラ有効
	bool isDebugcameraActive_ = false;
	//デバッグカメラの生成
	DebugCamera* debugCamera_ = nullptr;
	
	//自キャラ
	Player* player_ = nullptr;
	//敵キャラ
	std::list<Enemy*> enemy_;

	//背景
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	//レールカメラ
	RailCamera* railCamera_ = nullptr;
	// 弾
	std::list<EnemyBullet*> bullets_;
	//敵発生コマンド
	std::stringstream enemyPopCommands;

	//待機関連
	bool stopF = false;
	int32_t timer = 60;
};
