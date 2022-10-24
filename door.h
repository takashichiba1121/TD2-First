#pragma once

#include <memory>
#include "Input.h"
#include "DebugText.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "Model.h"

class door
{
public:
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

	/// <summary>
	/// �X�v���C�g�p�`��
	/// </summary>
	void SpriteDraw();

	bool GetMashFlag() { return mashFlag_; }

	void Reset();

	UINT GetMashNum() { return mashNum_; }

private:

	//�A�ŏ���
	void Mash();

	bool mashFlag_ = false;
	UINT mashNum_ = 0;

	uint32_t textureHandle_ = 0;

	std::unique_ptr<Sprite> sprite_;

	WorldTransform door1worldTransform_;
	WorldTransform door2worldTransform_;
	WorldTransform door3worldTransform_;

	std::unique_ptr<Model> door1model_;
	std::unique_ptr<Model> door2model_;
	std::unique_ptr<Model> door3model_;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

