#include "sky.h"

sky::sky()
{
}

sky::~sky()
{
}

void sky::Initialize()
{
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// スケールを設定
	worldTransform_.scale_ = { 250.0f,250.0f,250.0f };
	// スケーリング行列
	affine::makeMatIdentity(worldTransform_.matWorld_);
	affine::makeMatScale(worldTransform_.matWorld_, worldTransform_.scale_);
	affine::makeMatRot(worldTransform_.matWorld_, { 0,0,0 });
	affine::makeMatTrans(worldTransform_.matWorld_, { 0,0,0 });
	// 行列の転送
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
