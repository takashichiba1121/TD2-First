#include "stage.h"
#include"affine.h"
#include<cmath>
#include"MathUtility.h"

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

	Vector3 start = {0.0f,0.0f,0.0f};
	Vector3 gole = { 7.5f,0.0f,static_cast<float> (7.5 * sqrt(3))};
	Vector3 vector = {gole.x - start.x,gole.y- start.y,gole.z - start.z };
	float len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len != 0)
	{
		vector /= len;
	}

	for (int i = 0; i < 50; i++)
	{
		worldTransform_[i].Initialize();
		worldTransform2_[i].Initialize();

		worldTransform2_[i].rotation_ = {0.0f,30.0f * affine::Deg2Rad,0.0f};

		worldTransform_[i].translation_ = { 0.0f,-3.0f,i*15+7.0f };
		worldTransform2_[i].translation_ = { vector.x*15*i+vector.x*7,-3.0f,vector.z * 15 * i + vector.z * 7+750 };

		affine::makeMatIdentity(worldTransform_[i].matWorld_);
		affine::makeMatIdentity(worldTransform2_[i].matWorld_);
		affine::makeMatRot(worldTransform2_[i].matWorld_, worldTransform2_[i].rotation_);
		affine::makeMatTrans(worldTransform_[i].matWorld_, worldTransform_[i].translation_);
		affine::makeMatTrans(worldTransform2_[i].matWorld_, worldTransform2_[i].translation_);
		worldTransform_[i].TransferMatrix();
		worldTransform2_[i].TransferMatrix();
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
		model_->Draw(worldTransform2_[i], *viewProjection);
	}
}
