#include"player.h"
#include"affine.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(WorldTransform* worldTransform)
{
	model_.reset(Model::CreateFromOBJ("tire", true));
	worldTransform_.parent_ = worldTransform;
	worldTransform_.Initialize();
	worldTransform_.rotation_ = { 0.0f, 90.0f * affine::Deg2Rad, 0.0f };
	worldTransform_.translation_ = { 0.0f, 3.5f, 5.0f };

}

void Player::Update()
{
	worldTransform_.rotation_ += {0.01f, 0.0f, 0.0f};

	affine::makeAffine(worldTransform_);
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection* viewProjection)
{
	model_->Draw(worldTransform_, *viewProjection);
}
