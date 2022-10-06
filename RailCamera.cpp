#include "RailCamera.h"

RailCamera::RailCamera()
{
}

RailCamera::~RailCamera()
{
}

void RailCamera::Initialize(const Vector3& position, const Vector3& rotaion)
{
	//���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotaion;

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_->Initialize();

}

void RailCamera::Update(Vector3& move, Vector3& rot)
{
	using namespace MathUtility;

	//���[���h�g�����X�t�H�[���̐��l�����Z
	worldTransform_.translation_ += move;
	worldTransform_.rotation_ += rot;
	//���[���h�g�����X�t�H�[���̍X�V
	affine::makeAffine(worldTransform_);

	viewProjection_->eye = affine::GetWorldTrans(worldTransform_.matWorld_);
	//���[���h�O���x�N�g��
	Vector3 forward(0, 0, 1);
	//���[���J�����̉�]�𔽉f
	forward = forward * worldTransform_.matWorld_;
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	viewProjection_->target = viewProjection_->eye + forward;
	//���[���h����x�N�g��
	Vector3 up(0, 1, 0);
	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��)
	viewProjection_->up = up * worldTransform_.matWorld_;
	//�r���[�v���W�F�N�V�������X�V
	viewProjection_->UpdateMatrix();
	viewProjection_->TransferMatrix();
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
