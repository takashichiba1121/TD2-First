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
	//ワールド変換データ
	WorldTransform worldTransform_[50];
	WorldTransform worldTransform2_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	DebugText* debugText_ = nullptr;
};

