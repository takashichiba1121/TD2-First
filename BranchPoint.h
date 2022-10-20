#pragma once
#include"MathUtility.h"
#include"Model.h"
#include<memory>

class BranchPoint
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3& pos, Vector3& rot);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);
private:
	//本体
	std::unique_ptr<Model> bodyMode_;
	std::unique_ptr<WorldTransform> bodyWorldTransform_;

	//正解
	std::unique_ptr<Model> correctMode_;
	std::unique_ptr<WorldTransform> correctWorldTransform_;

	//不正解
	std::unique_ptr<Model> wrongMode_;
	std::unique_ptr<WorldTransform> wrongWorldTransform_;

};

