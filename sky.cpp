#include "sky.h"

sky::sky()
{
}

sky::~sky()
{
}

void sky::Initialize()
{
	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	// �X�P�[����ݒ�
	worldTransform_.scale_ = { 250.0f,250.0f,250.0f };
	// �X�P�[�����O�s��
	affine::makeMatIdentity(worldTransform_.matWorld_);
	affine::makeMatScale(worldTransform_.matWorld_, worldTransform_.scale_);
	affine::makeMatRot(worldTransform_.matWorld_, { 0,0,0 });
	affine::makeMatTrans(worldTransform_.matWorld_, { 0,0,0 });
	// �s��̓]��
	worldTransform_.TransferMatrix();

	model_.reset(Model::CreateFromOBJ("skydome", true));
}

void sky::Update()
{
}

void sky::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
