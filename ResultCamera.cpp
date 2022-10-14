#include "ResultCamera.h"
#include"affine.h"

ResultCamera::ResultCamera()
{
}

ResultCamera::~ResultCamera()
{
}

void ResultCamera::Initialize(WorldTransform* worldTransform)
{

	using namespace MathUtility;

	worldTransform_.parent_ = worldTransform;

	//���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.translation_ = {1.0f,-2.0f,11.0f};
	worldTransform_.rotation_ = {0.0,225.0f*affine::Deg2Rad,0.0f};

	viewProjection_ = std::make_unique<ViewProjection>();
	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_->Initialize();
}

void ResultCamera::Update()
{
	using namespace MathUtility;

	affine::makeAffine(worldTransform_);

	worldTransform_.matWorld_*= worldTransform_.parent_->matWorld_;

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