#include "RailCamera.h"

RailCamera::RailCamera()
{
}

RailCamera::~RailCamera()
{
}

void RailCamera::Initialize(const Vector3& position, const Vector3& rotaion)
{
	using namespace MathUtility;

	//���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotaion;

	debugText_ = DebugText::GetInstance();
	viewProjection_ = std::make_unique<ViewProjection>();
	viewProjection_->farZ = 12000.0f;
	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_->Initialize();

	Vector3 start = { 0.0f,0.0f,0.0f };
	Vector3 gole = { 7.5f,0.0f,static_cast<float> (7.5 * sqrt(3)) };
	vector = { gole.x - start.x,gole.y - start.y,gole.z - start.z };
	vector = Vector3Normalize(vector);

	rotRange[0] = 750.0f;
	rotRange[1] = rotRange[0] + vector.z * 750;
	rotRange[2] = 750.0f;
	rotRange[3] = 0.0f + speed * 5;
	rotRange[4] = rotRange[3] - vector.z * 750;
	rotRange[5] = 0.0f;
}

bool RailCamera::Update(bool GetCrashFlag)
{
	using namespace MathUtility;

	float playerz = 0.0f;

	if (!GetCrashFlag)
	{
		switch (currentSide)
		{
		case side::First:
		
			playerz = worldTransform_.translation_.z + 10.0f;
			if (playerz < rotRange[0] - (speed * 10))
			{
				Vector3 move = { 0,0,1.0f * speed };
				worldTransform_.translation_ += move;
				if (playerz  > rotRange[0]- (speed*10))
				{
					worldTransform_.translation_ = Vector3{ 0.0f,0.0f,rotRange[0]-speed*10 };
				}
			}
			else 
			{
				Vector3 move = { 0,0,1.0f * speed };
				Vector3 Rot = { 0,3.0f * affine::Deg2Rad,0 };

				if (worldTransform_.rotation_.y>=30.0f*affine::Deg2Rad)
				{
					worldTransform_.translation_ = { -vector.x * 10,0.0f,rotRange[0] - vector.z * 10 };

					currentSide = side::Second;
				}
				else
				{
					worldTransform_.rotation_+=(Rot);
					worldTransform_.translation_ += move;
				}
				if (worldTransform_.rotation_.y > 30.0f * affine::Deg2Rad)
				{
					worldTransform_.rotation_.y = 30.0f * affine::Deg2Rad;
				}
			}
			break;
		case side::Second:
			playerz = worldTransform_.translation_.z + vector.z*10;
			if (playerz < rotRange[1]-(vector.z* speed * 10))
			{
				Vector3 move = { vector * speed };
				worldTransform_.translation_ +=  move ;
				if (playerz > rotRange[1] - (vector.z*speed * 10))
				{
					worldTransform_.translation_ = Vector3{ 0.0f,0.0f,rotRange[2] - (vector.z * speed * 10) };
				}
			}
			else 
			{
				Vector3 move = { vector * speed };
				Vector3 Rot = { 0,12 * affine::Deg2Rad,0 };

				if(worldTransform_.rotation_.y >= 150.0f * affine::Deg2Rad)
				{
					worldTransform_.translation_ = { vector.x * 750 - vector.x * 10,0.0f,rotRange[1] + vector.z * 10 };
					currentSide = side::Third;
				}
				else
				{
					worldTransform_.rotation_ += (Rot);
					worldTransform_.translation_ += move;
				}
				if (worldTransform_.rotation_.y > 150.0f * affine::Deg2Rad)
				{
					worldTransform_.rotation_.y = 150.0f * affine::Deg2Rad;
				}
			}
			break;
		case side::Third:
			playerz = worldTransform_.translation_.z -vector.z * 10.0f;
			if (playerz > rotRange[2] + vector.z * (speed * 10))
			{
				Vector3 move = { vector.x * speed,vector.y * speed,-vector.z * speed };
				worldTransform_.translation_ += move;
				if (playerz < rotRange[2] + (vector.z * speed * 10))
				{
					worldTransform_.translation_ = Vector3{ 0.0f,0.0f,rotRange[2] + (vector.z * speed * 10) };
				}
			}
			else
			{
				Vector3 move = { vector.x * speed,vector.y * speed,-vector.z * speed };
				Vector3 Rot = { 0,3 * affine::Deg2Rad,0 };

				if (worldTransform_.rotation_.y >= 180.0f * affine::Deg2Rad)
				{
					worldTransform_.translation_ = { vector.x * 750 * 2,0.0f,750 + 10 };
					currentSide = side::Fourth;
				}
				else
				{
					worldTransform_.rotation_ += (Rot);
					worldTransform_.translation_ += move;
				}
				if (worldTransform_.rotation_.y > 180.0f * affine::Deg2Rad)
				{
					worldTransform_.rotation_.y = 180.0f * affine::Deg2Rad;
				}
			}
			break;
		case side::Fourth:
			playerz = worldTransform_.translation_.z - 10.0f;
			if (playerz > rotRange[3] +speed * 10)
			{
				Vector3 move = { 0,0,-1.0f * speed };
				worldTransform_.translation_ += move;
				if (playerz < rotRange[3] +  speed * 10)
				{
					worldTransform_.translation_ = Vector3{ 0.0f,0.0f,rotRange[3] + ( speed * 10) };
				}
			}
			else
			{
				Vector3 move = { 0,0,-1.0f * speed };
				Vector3 Rot = { 0,3 * affine::Deg2Rad,0 };

				if (worldTransform_.rotation_.y >= 210.0f * affine::Deg2Rad)
				{
					worldTransform_.translation_ = { vector.x * 750 * 2 + vector.x * 10,0.0f,vector.z * 10 };
					currentSide = side::Fifth;
				}
				else
				{
					worldTransform_.rotation_ += (Rot);
					worldTransform_.translation_ += move;
				}
				if (worldTransform_.rotation_.y > 210.0f * affine::Deg2Rad)
				{
					worldTransform_.rotation_.y = 210.0f * affine::Deg2Rad;
				}
			}
			break;
		case side::Fifth:
			playerz = worldTransform_.translation_.z -vector.z* 10.0f;
			if (playerz > rotRange[4] + speed * 10)
			{
				Vector3 move = { -vector.x * speed,-vector.y * speed,-vector.z * speed };
				worldTransform_.translation_ += move;
				if (playerz < rotRange[4] + speed * 10)
				{
					worldTransform_.translation_ = Vector3{ 0.0f,0.0f,rotRange[4] + (speed * 10) };
				}
			}
			else
			{
				Vector3 move = { -vector.x * speed,-vector.y * speed,-vector.z * speed };
				Vector3 Rot = { 0,12 * affine::Deg2Rad,0 };

				if (worldTransform_.rotation_.y >= 330.0f * affine::Deg2Rad)
				{
					worldTransform_.translation_ = { vector.x * 750 + vector.x * 10,0,rotRange[4] - vector.z * 10 };

					currentSide = side::Sixth;
				}
				else
				{
					worldTransform_.rotation_ += (Rot);
					worldTransform_.translation_ += move;
				}
				if (worldTransform_.rotation_.y > 330.0f * affine::Deg2Rad)
				{
					worldTransform_.rotation_.y = 330.0f * affine::Deg2Rad;
				}
			}
			break;
		case side::Sixth:
			playerz = worldTransform_.translation_.z +vector.z* 10.0f;
			if (playerz < rotRange[5] - speed * 10)
			{
				Vector3 move = { -vector.x * speed,vector.y * speed,vector.z * speed };
				worldTransform_.translation_ += move;
				if (playerz > rotRange[5] - speed * 10)
				{
					worldTransform_.translation_ = Vector3{ 0.0f,0.0f,rotRange[5] - (speed * 10) };
				}
			}
			else
			{
				Vector3 move = { -vector.x * speed,vector.y * speed,vector.z * speed };

				if (worldTransform_.rotation_.y >= 360.0f * affine::Deg2Rad)
				{
					worldTransform_.translation_ = { 0.0,0.0f,-10.0f };

					worldTransform_.rotation_.y = 0.0f;

					isActivationDoor = false;

					lap++;

					currentSide = side::First;
				}
				else
				{
					Vector3 Rot = { 0,3 * affine::Deg2Rad,0 };

					worldTransform_.rotation_ += (Rot);
					worldTransform_.translation_ += move;

					IsLapReset = true;
				}
				if (worldTransform_.rotation_.y > 360.0f * affine::Deg2Rad)
				{
					worldTransform_.rotation_.y = 360.0f * affine::Deg2Rad;
				}
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (currentSide)
		{
		case side::First:
			playerz = worldTransform_.translation_.z - 10.0f;
			if (playerz < rotRange[0])
			{
				Vector3 move = { 0,0,1.0f * (speed * 0.5f) };
				worldTransform_.translation_ += move;
			}
			else if (playerz >= rotRange[0])
			{
				Vector3 Rot = { 0,30 * affine::Deg2Rad,0 };

				worldTransform_.rotation_ += (Rot);
				worldTransform_.translation_ ={ -vector.x * 10,0.0f,-vector.z * 10 + 750 };

				currentSide = side::Second;
			}
			break;
		case side::Second:
			playerz = worldTransform_.translation_.z - vector.z * 10;
			if (playerz < rotRange[1])
			{
				Vector3 move = { vector * (speed * 0.3f) };
				worldTransform_.translation_ += move;
			}
			else if (playerz >= rotRange[1])
			{
				Vector3 Rot = { 0,120 * affine::Deg2Rad,0 };

				worldTransform_.rotation_ += (Rot);
				worldTransform_.translation_= { vector.x * 750 - vector.x * 10,0.0f,rotRange[1] + vector.z * 10 };
				currentSide = side::Third;
			}
			break;
		case side::Third:
			playerz = worldTransform_.translation_.z + vector.z * 10.0f;
			if (playerz > rotRange[2])
			{
				Vector3 move = { vector.x * (speed * 0.3f),vector.y * (speed * 0.3f),-vector.z * (speed * 0.3f) };
				worldTransform_.translation_ += move;
			}
			else if (playerz <= rotRange[2])
			{
				Vector3 Rot = { 0,30 * affine::Deg2Rad,0 };

				worldTransform_.rotation_ += (Rot);
				worldTransform_.translation_ ={ vector.x * 750 * 2,0.0f,750 + 10 };

				currentSide = side::Fourth;
			}
			break;
		case side::Fourth:
			playerz = worldTransform_.translation_.z + 10.0f;
			if (playerz > rotRange[3])
			{
				Vector3 move = { 0,0,-1.0f * (speed * 0.3f) };
				worldTransform_.translation_ += move;
			}
			if (playerz <= rotRange[3])
			{
				Vector3 Rot = { 0,30 * affine::Deg2Rad,0 };

				worldTransform_.rotation_ += (Rot);
				worldTransform_.translation_ ={ vector.x * 750 * 2 + vector.x * 10,0.0f,vector.z * 10 };

				currentSide = side::Fifth;
			}
			break;
		case side::Fifth:
			playerz = worldTransform_.translation_.z + vector.z * 10.0f;
			if (playerz > rotRange[4])
			{
				Vector3 move = { -vector.x * (speed * 0.3f),-vector.y * (speed * 0.3f),-vector.z * (speed * 0.3f) };
				worldTransform_.translation_ += move;
			}
			else if (playerz <= rotRange[4])
			{
				Vector3 Rot = { 0,120 * affine::Deg2Rad,0 };

				worldTransform_.rotation_ += (Rot);
				worldTransform_.translation_ ={ vector.x * 750 + vector.x * 10,0,rotRange[4] - vector.z * 10 };

				currentSide = side::Sixth;
			}
			break;
		case side::Sixth:
			playerz = worldTransform_.translation_.z - vector.z * 10.0f;
			if (playerz < rotRange[5])
			{
				Vector3 move = { -vector.x * (speed * 0.3f),vector.y * (speed * 0.3f),vector.z * (speed * 0.3f) };
				worldTransform_.translation_ += move;
			}
			else if (playerz >= rotRange[5])
			{
				Vector3 Rot = { 0,30 * affine::Deg2Rad,0 };

				worldTransform_.rotation_ += (Rot);
				worldTransform_.translation_ ={ 0.0,0.0f,-10.0f };

				IsLapReset = true;

				lap++;

				currentSide = side::First;
			}
			break;
		default:
			break;
		}
	}

	Move();

	debugText_->SetPos(10, 10);
	debugText_->Printf(" PlayerZ:%f", playerz);
	debugText_->SetPos(10, 30);
	debugText_->Printf(" RailCamera.RotY:%f", worldTransform_.rotation_.y/affine::Deg2Rad);
	debugText_->SetPos(10, 50);
	debugText_->Printf(" %d", currentSide);
	debugText_->SetPos(10, 70);
	debugText_->Printf(" lap:%d", lap);

	//�Z�p�`���l�ӖڂŃv���C���[��Z������������ĂȂ����̎��Ɉ����h�A���g���ĂȂ����̂�
	if (currentSide==side::Fourth&&playerz<=375.0f&&isActivationDoor==false) {
		isActivationDoor = true;
		return true;
	}

	return false;
}

void RailCamera::Draw(){}

ViewProjection* RailCamera::GetViewProjection()
{
	return viewProjection_.get();
}

WorldTransform* RailCamera::GetWorldTransformPtr()
{
	return &worldTransform_;
}

void RailCamera::Move()
{
	using namespace MathUtility;

	//���[���h�g�����X�t�H�[���̍X�V
	affine::makeAffine(worldTransform_);

	viewProjection_->eye = affine::GetWorldTrans(worldTransform_.matWorld_);
	//���[���h�O���x�N�g��
	Vector3 forward(0, 0, 1);
	//���[���J�����̉�]�𔽉f
	forward = affine::MatVector(worldTransform_.matWorld_, forward);
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	viewProjection_->target = viewProjection_->eye + forward;
	//���[���h����x�N�g��
	Vector3 up(0, 1, 0);
	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��)
	viewProjection_->up = affine::MatVector(worldTransform_.matWorld_, up);
	//�r���[�v���W�F�N�V�������X�V
	viewProjection_->UpdateMatrix();
	viewProjection_->TransferMatrix();
}
float RailCamera::GetWorldTransformRot()
{
	return worldTransform_.rotation_.z;
}
void RailCamera::reset(){
	worldTransform_.translation_ = Vector3(0.0f,0.0f,-10.0f);
	worldTransform_.rotation_ = Vector3(0,0,0);

	speed = 1;
	currentSide = side::First;

	isActivationDoor = false;
}

void RailCamera::lapReset()
{
	isActivationDoor = false;
	IsLapReset = false;
}

void RailCamera::SpeedUp()
{
	speed++;
}

void RailCamera::SpeedDown()
{
	speed--;
}
