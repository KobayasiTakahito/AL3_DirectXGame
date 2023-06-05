#pragma once
#include<WorldTransform.h>
#include<Model.h>

class Skydome {
public:
	void Initializa(Model* model);

	void Update();

	void Draw(ViewProjection& viewprojection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

};
