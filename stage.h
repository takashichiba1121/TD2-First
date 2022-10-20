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
	//WorldTransform worldTransform_[50];
	//WorldTransform worldTransform2_[50];
	//WorldTransform worldTransform3_[50];
	//WorldTransform worldTransform4_[50];
	//WorldTransform worldTransform5_[50];
	//WorldTransform worldTransform6_[50];

	WorldTransform stageWorldTransform_;
	//モデル
	//Model* model_ = nullptr;
	Model* stage_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	DebugText* debugText_ = nullptr;

	Vector3 vector = {};
};

