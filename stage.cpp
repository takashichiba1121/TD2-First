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
	model_ = Model::CreateFromOBJ("straightRoad", true);
	/*textureHandle_ = TextureManager::Load("uvChecker.png");*/

	for (int i = 0; i < 50; i++)
	{
		worldTransform_[i].Initialize();
		worldTransform2_.Initialize();

		worldTransform2_.rotation_ = { 0.0f,25.0f * affine::Deg2Rad,0.0f };

		worldTransform_[i].translation_ = { 0.0f,-3.0f,i*15+7.0f };
		worldTransform2_.translation_ = { 20.0f,-3.0f,100.0f };

		affine::makeMatIdentity(worldTransform_[i].matWorld_);
		affine::makeMatIdentity(worldTransform2_.matWorld_);
		affine::makeMatRot(worldTransform2_.matWorld_, worldTransform2_.rotation_);
		affine::makeMatTrans(worldTransform_[i].matWorld_, worldTransform_[i].translation_);
		affine::makeMatTrans(worldTransform2_.matWorld_, worldTransform2_.translation_);
		worldTransform_[i].TransferMatrix();
		worldTransform2_.TransferMatrix();
	}
}

void stage::Update()
{
}

void stage::Draw(ViewProjection* viewProjection)
{
	for (int i = 0; i < 50; i++)
	{
		model_->Draw(worldTransform_[i], *viewProjection);
	}
	/*model_->Draw(worldTransform2_, *viewProjection, textureHandle_);*/
}
