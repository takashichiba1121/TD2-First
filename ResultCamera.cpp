#include "ResultCamera.h"

ResultCamera::ResultCamera()
{
}

ResultCamera::~ResultCamera()
{
}

void ResultCamera::Initialize(const Vector3& position, const Vector3& rotaion)
{
	//���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotaion;

	viewProjection_ = std::make_unique<ViewProjection>();
	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_->Initialize();
}

void ResultCamera::Update(WorldTransform worldTransform)
{
	using namespace MathUtility;


	Vector3 move(0, 0, 0);
	Vector3 front;
	Vector3 frontVec;
	Vector3 frontNormVec;

	float rotationSpeed = 0.01f;

	front.x = worldTransform.translation_.x + cosf(worldTransform.rotation_.y - affine::PIHalf);
	front.y = worldTransform.translation_.y + cosf(worldTransform.rotation_.x - affine::PIHalf);
	front.z = worldTransform.translation_.z - sinf(worldTransform.rotation_.y - affine::PIHalf);


	frontVec = front - worldTransform.translation_;
	frontNormVec = MathUtility::Vector3Normalize(frontVec);
	frontVec = frontNormVec;

	float speed_ = 0.01f;

	Vector3 moveSpeed_ = speed_ * frontNormVec;

	//���[���h�g�����X�t�H�[���̐��l�����Z
	worldTransform.translation_.x += moveSpeed_.x;
	worldTransform.translation_.y += moveSpeed_.y;
	worldTransform.translation_.z += moveSpeed_.z;

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

void ResultCamera::Draw() {}

ViewProjection* ResultCamera::GetViewProjection()
{
	return viewProjection_.get();
}

WorldTransform* ResultCamera::GetWorldTransformPtr()
{
	return &worldTransform_;
}