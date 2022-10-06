#include"player.h"

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
}

void Player::Update()
{
	worldTransform_.rotation_ += {1.0f, 0.0f, 0.0f};
}

void Player::Draw(ViewProjection* viewProjection)
{
	model_->Draw(worldTransform_, *viewProjection);
}
