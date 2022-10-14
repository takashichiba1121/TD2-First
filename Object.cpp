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

bool CheckAABB2AABB(AABB& aabb1, AABB& aabb2)
{
	std::array<Vector3, 2> min_;
	min_[0] = { aabb1.center.x - aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	min_[1] = { aabb2.center.x - aabb2.size.x, aabb2.center.y - aabb2.size.y ,aabb2.center.z - aabb2.size.z };
	std::array<Vector3, 2> max_;
	max_[0] = { aabb1.center.x + aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z + aabb1.size.z };
	max_[1] = { aabb2.center.x + aabb2.size.x, aabb2.center.y + aabb2.size.y ,aabb2.center.z + aabb2.size.z };

	if (min_[0].x > max_[1].x || max_[0].x < min_[1].x ||
		min_[0].y > max_[1].y || max_[0].y < min_[1].y ||
		min_[0].z > max_[1].z || max_[0].z < min_[1].z)
	{
		return false;
	}

	return true;
}

bool Object::GetIsDeath()
{
	return IsDeath;
}

void Object::OnCollision()
{
	IsDeath = true;
}