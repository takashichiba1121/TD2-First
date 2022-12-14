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
	void Initialize(Vector3 trans,Vector3 Rot);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Vector3 vector);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	bool GetMashFlag() { return mashFlag_; }

	void Reset(Vector3 trans);

	UINT GetMashNum() { return mashNum_; }

private:

	//連打処理
	void Mash(Vector3 vector);

	bool mashFlag_ = false;
	UINT mashNum_ = 0;

	WorldTransform door1worldTransform_;
	WorldTransform door2worldTransform_;
	WorldTransform door3worldTransform_;

	std::unique_ptr<Model> door1model_;
	std::unique_ptr<Model> door2model_;
	std::unique_ptr<Model> door3model_;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

