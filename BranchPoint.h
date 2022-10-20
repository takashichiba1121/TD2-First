#pragma once
#include"MathUtility.h"
#include"Model.h"
#include<memory>
#include"affine.h"
#include"RailCamera.h"
#include"Player.h"
#include<functional>
class BranchPoint
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& pos, const Vector3& rot, const Vector3& size, Model* bodyModel, Model* correctModel, Model* wrongModel, std::function<void(void)>left, std::function<void(void)>right);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	void DebugDraw();

private:
	//本体
	Model* bodyModel_ = nullptr;
	std::unique_ptr<WorldTransform> bodyWorldTransform_;

	//正解
	Model* correctModel_ = nullptr;
	std::unique_ptr<WorldTransform> correctWorldTransform_;

	//不正解
	Model* wrongModel_ = nullptr;
	std::unique_ptr<WorldTransform> wrongWorldTransform_;
	AABB collider_;

	std::function<void()>left_;
	std::function<void()>right_;

	bool passingFlag_ = false;
};

