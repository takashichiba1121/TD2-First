#include "Object.h"

void Object::Initialize(Vector3 pos, Vector3 size, Model* model)
{
	worldTransform_ = std::make_unique<WorldTransform>();

	worldTransform_->translation_ = pos;
	worldTransform_->scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_->rotation_ = { 0.0f,0.0f,0.0f };

	worldTransform_->Initialize();

	model_ = model;

	collider_.center = worldTransform_->translation_;
	collider_.size = {
		1.0f * worldTransform_->scale_.x,
		1.0f * worldTransform_->scale_.y,
		1.0f * worldTransform_->scale_.z };
}

void Object::Update(Vector3 playerPos)
{
	affine::makeAffine(*worldTransform_);

	worldTransform_->TransferMatrix();
}

void Object::Draw(ViewProjection* viewProjection)
{
	model_->Draw(*worldTransform_, *viewProjection);
}

AABB& Object::GetCollider()
{
	return collider_;
}



bool Object::GetIsDeath()
{
	return IsDeath;
}

void Object::OnCollision()
{
	IsDeath = true;
}