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

	bool GetMashFlag() { return mashFlag_; }

	UINT GetMashNum() { return mashNum_; }

private:

	//連打処理
	void Mash();

	bool mashFlag_ = false;
	UINT mashNum_ = 0;

	WorldTransform worldTransform_;
	std::unique_ptr<Model> model_;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

