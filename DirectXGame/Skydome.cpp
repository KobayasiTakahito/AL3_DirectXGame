#include "Skydome.h"
#include <cassert>

void Skydome::Initializa(Model* model) {
	assert(model);
	model_ = model;
	
	worldTransform_.Initialize();
}

void Skydome::Update() {

}

void Skydome::Draw(ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection);
}