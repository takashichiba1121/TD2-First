#include "Object.h"

void Object::Initialize(const Vector3& pos, const Vector3& rot, float radius, Model* model)
{
	worldTransform_ = std::make_unique<WorldTransform>();

	worldTransform_->translation_ = pos;
	worldTransform_->scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_->rotation_ = rot;

	worldTransform_->Initialize();

	model_ = model;

	collider_.center = worldTransform_->translation_;
	collider_.radius = radius;
}

void Object::Update()
{
	affine::makeAffine(*worldTransform_);

	worldTransform_->TransferMatrix();
}

void Object::Draw(ViewProjection* viewProjection)
{
	model_->Draw(*worldTransform_, *viewProjection);
}

SPHERE& Object::GetCollider()
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