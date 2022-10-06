#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class stage
{
public:
	stage();
	~stage();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* viewProjection);


private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	WorldTransform worldTransform2_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	DebugText* debugText_ = nullptr;
};

