#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "input.h"

class Player {
public:
	//初期化
	void Initialize(Model* model,uint32_t &textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection &viewprojection);

	//Vec３の加算
	Vector3 Vec3Add(Vector3 add1, Vector3 add2) { 
		Vector3 add3;
		 add3.x = add1.x + add2.x;
		 add3.y = add1.y + add2.y;
		 add3.z = add1.z + add2.z;
		 return add3;
	}

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t texturehandle_ = 0u;
	//自キャラ
	Player* player_ = nullptr;
	//キーボード入植
	Input* input_ = nullptr;
};
