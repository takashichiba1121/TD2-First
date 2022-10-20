#pragma once
#include"affine.h"
#include<list>
#include"BranchPoint.h"

class SpeedUpChance
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(RailCamera* railCamera);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Player* player, RailCamera* railCamera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	void DebugDraw();

private:
	std::list<std::unique_ptr<BranchPoint>>branchPoints;

	//本体
	std::unique_ptr<Model> bodyModel_;

	//正解
	std::unique_ptr<Model> correctModel_;

	//不正解
	std::unique_ptr<Model> wrongModel_;

};

