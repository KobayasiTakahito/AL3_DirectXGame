#include "RailCamera.h"
#include "world.h"
#include "ImGuiManager.h"
void RailCamera::Initializ(Vector3 worldTransForm ,Vector3 rotate){ 
	worldTransform_.translation_ = worldTransForm;
	worldTransform_.rotation_ = rotate;

	viewProjection_.Initialize();
	

};


void RailCamera::Update(){
	worldTransform_.translation_.z += 0.1f;
	worldTransform_.rotation_.y += 0.001f;
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    {1.0f, 1.0f, 1.0f}, worldTransform_.rotation_, worldTransform_.translation_);
	
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	//デバッグカメラ
	ImGui::Begin("Camera");
	ImGui::DragFloat3("CameraTranslate", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("CameraRotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
	
};