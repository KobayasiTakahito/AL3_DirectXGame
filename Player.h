#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Player {
public:
	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();


private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t texturehandle_ = 0u;
	//���L����
	Player* player_ = nullptr;

};
