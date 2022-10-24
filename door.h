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
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	/// <summary>
	/// スプライト用描画
	/// </summary>
	void SpriteDraw();

	bool GetMashFlag() { return mashFlag_; }

	void Reset();

	UINT GetMashNum() { return mashNum_; }

private:

	//連打処理
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

