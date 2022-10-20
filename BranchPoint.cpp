#include "BranchPoint.h"

void BranchPoint::SpeedUpChance(Vector3& pos)
{
}

void BranchPoint::Initialize(Vector3& pos, Vector3& rot)
{
	bodyWorldTransform_ = std::make_unique<WorldTransform>();
	bodyWorldTransform_->translation_ = pos;
	bodyWorldTransform_->translation_ = { 12.0f,12.0f,12.0f };
	bodyWorldTransform_->rotation_ = rot;
	bodyWorldTransform_->Initialize();

	correctWorldTransform_ = std::make_unique<WorldTransform>();
	correctWorldTransform_->parent_ = bodyWorldTransform_.get();
	correctWorldTransform_->translation_ = { 12.0f,12.0f,12.0f };
	correctWorldTransform_->Initialize();

	wrongWorldTransform_ = std::make_unique<WorldTransform>();
	wrongWorldTransform_->parent_ = bodyWorldTransform_.get();
	wrongWorldTransform_->translation_ = { 12.0f,12.0f,12.0f };
	wrongWorldTransform_->Initialize();

}

void BranchPoint::Update()
{
}

void BranchPoint::Draw(ViewProjection* viewProjection)
{
	bodyMode_->Draw(*bodyWorldTransform_, *viewProjection);
	correctMode_->Draw(*correctWorldTransform_, *viewProjection);
	wrongMode_->Draw(*wrongWorldTransform_,*viewProjection);
}
