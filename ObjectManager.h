#pragma once
#include"Object.h"
#include"affine.h"
#include"MathUtility.h"
#include"player.h"


class ObjectManager
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Player* player);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* ViewProjection);

	void DebugDraw();

	void  Reset();

private:

	std::list<std::unique_ptr<Object>>objects_;
	Player* player_ = nullptr;
};

