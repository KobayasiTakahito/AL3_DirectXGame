#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Player {
public:
	//初期化
	void Initialize(Model* model,uint32_t &textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection &viewprojection);


private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t texturehandle_ = 0u;
	//自キャラ
	Player* player_ = nullptr;

};
