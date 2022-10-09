#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "affine.h"

class sky
{
public:
	sky();
	~sky();

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
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	std::unique_ptr<Model> model_;
};

