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

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	std::unique_ptr<Model> model_;
};

