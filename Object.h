#pragma once
#include<list>
#include<memory>
#include<Model.h>
#include"WorldTransform.h"
#include"ViewProjection.h"

class Object
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 pos);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Vector3 playerPos);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* ViewProjection);
private:

	std::unique_ptr<Model> model_;
	std::unique_ptr<WorldTransform> worldTransform_;
};

