#pragma once
#include"Object.h"
#include"affine.h"

class ObjectManager
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WorldTransform* playerWorldTransform);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* ViewProjection);

private:

	std::list<std::unique_ptr<Object>>objects_;
	WorldTransform* playerWorldTransform_;
};

