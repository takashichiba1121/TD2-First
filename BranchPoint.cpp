#include "BranchPoint.h"

void BranchPoint::Initialize(const Vector3& pos, const Vector3& rot, const Vector3& size, Model* bodyModel, Model* correctModel, Model* wrongModel, std::function<void(void)>left, std::function<void(void)>right)
{
	bodyModel_ = bodyModel;
	bodyWorldTransform_ = std::make_unique<WorldTransform>();
	bodyWorldTransform_->translation_ = pos;
	bodyWorldTransform_->scale_ = { 1.0f,1.0f,1.0f };
	bodyWorldTransform_->rotation_ = rot;
	bodyWorldTransform_->Initialize();
	affine::makeAffine(*bodyWorldTransform_);
	bodyWorldTransform_->TransferMatrix();

	//correctModel_ = correctModel;
	//correctWorldTransform_ = std::make_unique<WorldTransform>();
	//correctWorldTransform_->parent_ = bodyWorldTransform_.get();
	//correctWorldTransform_->scale_ = { 1.0f,1.0f,0.1f };
	//correctWorldTransform_->translation_ = { 0.0f,0.0f,0.0f };
	//correctWorldTransform_->Initialize();
	//affine::makeAffine(*correctWorldTransform_);
	//correctWorldTransform_->matWorld_ *= correctWorldTransform_->parent_->matWorld_;
	//correctWorldTransform_->TransferMatrix();

	//wrongModel_ = wrongModel;
//	wrongWorldTransform_ = std::make_unique<WorldTransform>();
//	wrongWorldTransform_->parent_ = bodyWorldTransform_.get();
////	wrongWorldTransform_->scale_ = { 12.0f,12.0f,12.0f };
//	wrongWorldTransform_->translation_ = {};
//	wrongWorldTransform_->Initialize();
//	affine::makeAffine(*wrongWorldTransform_);
//	wrongWorldTransform_->matWorld_ *= wrongWorldTransform_->parent_->matWorld_;
//	wrongWorldTransform_->TransferMatrix();

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
	//bodyModel_->Draw(*bodyWorldTransform_, *viewProjection);
	//correctModel_->Draw(*correctWorldTransform_, *viewProjection);
	//wrongModel_->Draw(*wrongWorldTransform_,*viewProjection);
}

void BranchPoint::DebugDraw()
{
	collider_.DebugDraw();
}
