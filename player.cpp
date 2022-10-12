#include"player.h"


void Player::Complement(float& x1, float x2, float flame)//ˆÚ“®•âŠ®
{
	float distanceX = x2 - x1;//‹——£‚ðo‚·
	float dividedDistanceX = distanceX / flame;//‹——£‚ðflame‚ÅŠ„‚Á‚½’l

	x1 += dividedDistanceX;//‹——£‚ðflame‚ÅŠ„‚Á‚½’l‚ð‘«‚·
}

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
	//worldTransform_.rotation_ = { 0.0f, defAngle, 0.0f };
	worldTransform_.translation_ = { 0.0f, -2.0f, 10.0f };

}

void Player::Update()
{
	worldTransform_.rotation_ += {0.0f, 0.0f, 0.01f};
	Rotate();

	Move();



	affine::makeAffine(worldTransform_);
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection* viewProjection)
{
	model_->Draw(worldTransform_, *viewProjection);
}

void Player::Move()
{
	if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		worldTransform_.translation_ += {-0.01f, 0.0f, 0.0f};
	}
	else if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		worldTransform_.translation_ += {0.01f, 0.0f, 0.0f};
	}
}

void Player::Rotate()
{
	if (Input::GetInstance()->PushKey(DIK_A))
	{
		Complement(worldTransform_.rotation_.x, 10.0f * affine::Deg2Rad, 40);//‰¡
		Complement(worldTransform_.rotation_.y, -28.0f * affine::Deg2Rad, 40);//‰¡

	}
	else if (Input::GetInstance()->PushKey(DIK_D))
	{
		Complement(worldTransform_.rotation_.x, -10.0f * affine::Deg2Rad, 40);//‰¡
		Complement(worldTransform_.rotation_.y, 28.0f * affine::Deg2Rad, 40);//‰¡
	}
	else
	{
		Complement(worldTransform_.rotation_.x, 0.0f, 40);//‰¡
		Complement(worldTransform_.rotation_.y, 0.0f, 40);//‰¡
	}
}
