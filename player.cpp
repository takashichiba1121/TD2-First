#include"player.h"
#include<DirectXMath.h>

void Player::Complement(float& x1, float x2, float flame)//移動補完
{
	float distanceX = x2 - x1;//距離を出す
	float dividedDistanceX = distanceX / flame;//距離をflameで割った値

	x1 += dividedDistanceX;//距離をflameで割った値を足す
}

Player::Player()
{
}

Player::~Player()
{
}

AABB& Player::GetCollider()
{
	return collider_;
}

void Player::OnCollision()
{
	crashFlag = true;
	crashTime = 70;
	oldRot.y = worldTransform_.rotation_.y;

}

bool Player::GetCrashFlag()
{
	return crashFlag;
}

void Player::Initialize(WorldTransform* worldTransform)
{
	model_.reset(Model::CreateFromOBJ("tire", true));
	worldTransform_.parent_ = worldTransform;
	worldTransform_.translation_ = { 0.0f, -2.0f, 10.0f };
	worldTransform_.Initialize();

	collider_.center = affine::GetWorldTrans(worldTransform_.matWorld_);

	//当たり判定の大きさ
	collider_.size = {
		0.3f * worldTransform_.scale_.x,
		0.5f * worldTransform_.scale_.y,
		0.5f * worldTransform_.scale_.z };
}

void Player::Update()
{
	if (!crashFlag)
	{
		if (!rollStopFlag)
		{
			worldTransform_.rotation_ += {0.2f, 0.0f, 0.0f};
		}

		//移動
		Move();
		//しゃがむ
		Squat();
		//旋回
		Rotate();

		if (Input::GetInstance()->TriggerKey(DIK_SPACE) && jumpFlag == 0 && !squatFlag)
		{
			jumpFlag = 1;
		}
	}
	else
	{
		if (jumpFlag ==1)
		{
			jumpFlag = 2;
		}

		worldTransform_.rotation_ += {0.0f, 0.4f, 0.0f};

		crashTime--;

		if (crashTime == 0)
		{
			crashFlag = false;
			worldTransform_.rotation_.y = oldRotY;
			crashTime = 70;
		}
	}

	//ジャンプ
	Jump();

	//ローカル行列計算
	affine::makeAffine(worldTransform_);
	//親子関係計算
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;

	collider_.center = affine::GetWorldTrans(worldTransform_.matWorld_);
	worldTransform_.TransferMatrix();
}

void Player::titleUpdate(){
		if (!rollStopFlag)
		{
			worldTransform_.rotation_ += {0.2f, 0.0f, 0.0f};
		}

	//ローカル行列計算
	affine::makeAffine(worldTransform_);
	//親子関係計算
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;

	collider_.center = affine::GetWorldTrans(worldTransform_.matWorld_);
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

	//移動制限
	{
		const float moveLimitX = 4.5;

		worldTransform_.translation_.x = max(worldTransform_.translation_.x, -moveLimitX);
		worldTransform_.translation_.x = min(worldTransform_.translation_.x, moveLimitX);
	}
}

void Player::Rotate()
{

	if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		Complement(worldTransform_.rotation_.y, -40.0f * affine::Deg2Rad, 10);//横

	}
	else if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		Complement(worldTransform_.rotation_.y, 40.0f * affine::Deg2Rad, 10);//横
	}
	else
	{
		Complement(worldTransform_.rotation_.y, 0.0f, 10);//横
	}
}

void Player::Jump()
{
	if (jumpFlag == 1)
	{
		worldTransform_.translation_.y += gravitySpeed;
		gravitySpeed -= 0.05f;

		if (gravitySpeed <= 0)
		{
			jumpFlag = 2;
		}
	}

	//下がる
	if (jumpFlag == 2)
	{
		worldTransform_.translation_.y -= gravitySpeed;
		gravitySpeed += 0.04f;

		if (gravitySpeed >= defGravitySpeed)
		{
			jumpFlag = 0;
			gravitySpeed = defGravitySpeed;
			worldTransform_.translation_.y = -2.0f;
		}
	}
}

void Player::Squat()
{
	if (Input::GetInstance()->TriggerKey(DIK_DOWN) && !jumpFlag && !squatFlag ||
		Input::GetInstance()->TriggerKey(DIK_S) && !jumpFlag && !squatFlag)
	{
		squatFlag = true;
		rollStopFlag = true;
		oldRot = worldTransform_.rotation_;
		worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };
		worldTransform_.rotation_.z = 80.0f * affine::Deg2Rad;

		collider_.size = {
		0.5f * worldTransform_.scale_.x,
		0.3f * worldTransform_.scale_.y,
		0.5f * worldTransform_.scale_.z };

	}

	if (squatFlag)
	{
		worldTransform_.rotation_.y = -90.0f * affine::Deg2Rad;

		squatTime--;

		if (squatTime == 0)
		{
			squatTime = 60 * 2;
			squatFlag = false;
			rollStopFlag = false;
			worldTransform_.rotation_ = oldRot;

			//当たり判定の大きさ
			collider_.size = {
				0.3f * worldTransform_.scale_.x,
				0.5f * worldTransform_.scale_.y,
				0.5f * worldTransform_.scale_.z };
		}
	}
}
