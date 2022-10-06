#include "stage.h"
#include"affine.h"

stage::stage()
{
}

stage::~stage()
{
	delete model_;
}

void stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	textureHandle_ = TextureManager::Load("uvChecker.png");

	worldTransform_.Initialize();
	worldTransform2_.Initialize();

	worldTransform_.scale_ = {5.0f,1.0f,50.0f};
	worldTransform2_.scale_ = { 5.0f,1.0f,50.0f };

	worldTransform2_.rotation_ ={0.0f,25.0f * affine::Deg2Rad,0.0f};
	
	worldTransform_.translation_ = {0.0f,-3.0f,20.0f};
	worldTransform2_.translation_ = {20.0f,-3.0f,100.0f };

	affine::makeMatIdentity(worldTransform_.matWorld_);
	affine::makeMatIdentity(worldTransform2_.matWorld_);
	affine::makeMatScale(worldTransform_.matWorld_,worldTransform_.scale_);
	affine::makeMatScale(worldTransform2_.matWorld_, worldTransform2_.scale_);
	affine::makeMatRot(worldTransform2_.matWorld_,worldTransform2_.rotation_);
	affine::makeMatTrans(worldTransform_.matWorld_,worldTransform_.translation_);
	affine::makeMatTrans(worldTransform2_.matWorld_, worldTransform2_.translation_);
	worldTransform_.TransferMatrix();
	worldTransform2_.TransferMatrix();
}

void stage::Update()
{
}

void stage::Draw(ViewProjection* viewProjection)
{
	model_->Draw(worldTransform_, *viewProjection, textureHandle_);
	model_->Draw(worldTransform2_, *viewProjection, textureHandle_);
}
