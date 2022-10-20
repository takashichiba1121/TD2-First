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
	/// ������
	/// </summary>
	void Initialize(const Vector3& pos, const Vector3& rot, const Vector3& size, Model* bodyModel, std::function<void(void)>left, std::function<void(void)>right);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	void DebugDraw();

private:
	//�{��
	Model* bodyModel_ = nullptr;
	std::unique_ptr<WorldTransform> bodyWorldTransform_;

	AABB collider_;

	std::function<void()>left_;
	std::function<void()>right_;

	bool passingFlag_ = false;
};

