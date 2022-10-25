#include "Goal.h"

void Goal::Initialize()
{
	worldTransform_ = std::make_unique<WorldTransform>();
	worldTransform_->Initialize();

	worldTransform_->translation_ = { 18.0f,-3.0f,-30.0f };
	worldTransform_->scale_ = { 4.0f,4.0f,4.0f };
	worldTransform_->rotation_ = { 0.0f,150.0f * affine::Deg2Rad, 0.0f };

	model_.reset(Model::CreateFromOBJ("goal", true));

	affine::makeAffine(*worldTransform_);

	worldTransform_->TransferMatrix();
}

void Goal::Draw(ViewProjection* viewProjection)
{
	model_->Draw(*worldTransform_, *viewProjection);
}