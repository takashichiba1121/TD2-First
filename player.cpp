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
	worldTransform_.rotation_ += {0.2f, 0.0f, 0.0f};

	Move();

	Jump();

	Rotate();

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
		worldTransform_.translation_ += {-0.03f, 0.0f, 0.0f};
	}
	else if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		worldTransform_.translation_ += {0.03f, 0.0f, 0.0f};
	}

	//ˆÚ“®§ŒÀ
	{
		const float moveLimitX = 4.5;

		worldTransform_.translation_.x = max(worldTransform_.translation_.x, -moveLimitX);
		worldTransform_.translation_.x = min(worldTransform_.translation_.x, moveLimitX);
	}
}

void Player::Rotate()
{
	//if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT))
	//{
	//	Complement(worldTransform_.rotation_.y, -28.0f * affine::Deg2Rad, 20);//‰¡

	//}
	//else if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_LEFT))
	//{
	//	Complement(worldTransform_.rotation_.y, 28.0f * affine::Deg2Rad, 20);//‰¡
	//}
	//else
	//{
	//	Complement(worldTransform_.rotation_.y, 0.0f, 20);//‰¡
	//}

	if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		Complement(worldTransform_.rotation_.y, -28.0f * affine::Deg2Rad, 40);//‰¡

	}
	else if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		Complement(worldTransform_.rotation_.y, 28.0f * affine::Deg2Rad, 40);//‰¡
	}
	else
	{
		Complement(worldTransform_.rotation_.y, 0.0f, 40);//‰¡
	}
}

void Player::Jump()
{
	if (Input::GetInstance()->PushKey(DIK_SPACE)&& jumpFlag == 0)
	{
		jumpFlag = 1;
	}

	if (jumpFlag == 1)
	{
		worldTransform_.translation_.y += gravitySpeed;
		gravitySpeed-=0.05f;

		if (gravitySpeed <= 0)
		{
			jumpFlag = 2;
		}
	}

	//‰º‚ª‚é
	if (jumpFlag == 2)
	{
		worldTransform_.translation_.y -= gravitySpeed;
		gravitySpeed+= 0.04f;

		if (gravitySpeed >= defGravitySpeed)
		{
			jumpFlag = 0;
			gravitySpeed = defGravitySpeed;
			worldTransform_.translation_.y = -2.0f;
		}

	}
}
