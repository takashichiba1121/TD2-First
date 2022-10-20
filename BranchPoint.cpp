#include "BranchPoint.h"

void BranchPoint::Initialize(const Vector3& pos, const Vector3& rot, const Vector3& size, Model* bodyModel, std::function<void(void)>left, std::function<void(void)>right)
{
	bodyModel_ = bodyModel;
	bodyWorldTransform_ = std::make_unique<WorldTransform>();
	bodyWorldTransform_->translation_ = pos;
	bodyWorldTransform_->scale_ = { 12.0f,12.0f,12.0f };
	bodyWorldTransform_->rotation_ = rot;
	bodyWorldTransform_->Initialize();
	affine::makeAffine(*bodyWorldTransform_);
	bodyWorldTransform_->TransferMatrix();

	collider_.center = affine::GetWorldTrans(bodyWorldTransform_->matWorld_);
	collider_.size = {
		size.x* bodyWorldTransform_->scale_.x,
		size.y* bodyWorldTransform_->scale_.y,
		size.z* bodyWorldTransform_->scale_.z };

	left_ = left;
	right_ = right;
}

void BranchPoint::Update(Player* player)
{
	if (!passingFlag_&&CheckAABB2AABB(player->GetCollider(), collider_))
	{
		passingFlag_ = true;

		if (player->GetWorldTransform().translation_.x > 0)
		{
			left_();
		}
		else
		{
			right_();
		}
	}
}

void BranchPoint::Draw(ViewProjection* viewProjection)
{
	bodyModel_->Draw(*bodyWorldTransform_, *viewProjection);

}

void BranchPoint::DebugDraw()
{
	collider_.DebugDraw();
}
