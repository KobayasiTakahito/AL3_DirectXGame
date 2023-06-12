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

	// 弾
	std::list<EnemyBullet*> bullets_;
	const std::list<EnemyBullet*>& GetBullets() { return bullets_; }
	


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
	//デバッグカメラ有効
	bool isDebugcameraActive_ = false;
	//デバッグカメラの生成
	DebugCamera* debugCamera_ = nullptr;
	
	//自キャラ
	Player* player_ = nullptr;
	//敵キャラ
	Enemy* enemy_ = nullptr;

	//背景
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	//レールカメラ
	RailCamera* railCamera_ = nullptr;
	// 弾
	EnemyBullet* bullet_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
