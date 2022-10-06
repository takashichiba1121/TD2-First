#include"player.h"
#include"affine.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	model_.reset(Model::CreateFromOBJ("tire", true));
	worldTransform_.Initialize();
	worldTransform_.rotation_ = { 0.0f, 90.0f * affine::Deg2Rad, 0.0f };

}

void Player::Update()
{
	worldTransform_.rotation_ += {0.01f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, -1.0f, -45.0f};

	affine::makeAffine(worldTransform_);

	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection* viewProjection)
{
	model_->Draw(worldTransform_, *viewProjection);
}
