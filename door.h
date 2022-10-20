#pragma once

#include <memory>
#include "Input.h"
#include "DebugText.h"
#include "WorldTransform.h"
#include "Model.h"

class door
{
public:

	door();

	~door();

	// <summary>
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

	bool GetMashFlag() { return mashFlag_; }

	void ResetMashFlag() { mashFlag_=false; }

	UINT GetMashNum() { return mashNum_; }

private:

	//�A�ŏ���
	void Mash();

	bool mashFlag_ = false;
	UINT mashNum_ = 0;

	WorldTransform worldTransform_;
	std::unique_ptr<Model> model_;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

