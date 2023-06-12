#pragma once
#include<WorldTransform.h>
#include<ViewProjection.h>
class RailCamera {
public:
	void Initializ(Vector3 worldTransForm,Vector3 rotate);
	void Update();
	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};
