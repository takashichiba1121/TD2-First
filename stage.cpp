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
	delete stage_;
}

void stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::CreateFromOBJ("straightRoad", true);
	stage_ = Model::CreateFromOBJ("stage", true);
	/*textureHandle_ = TextureManager::Load("uvChecker.png");*/

	Vector3 start = { 0.0f,0.0f,0.0f };
	Vector3 gole = { 7.5f,0.0f,static_cast<float> (7.5 * sqrt(3)) };
	vector = { gole.x - start.x,gole.y - start.y,gole.z - start.z };
	float len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len != 0)
	{
		vector /= len;
	}


	worldTransform7_.Initialize();
	worldTransform7_.translation_ = { 54.05f,-3.0f,32.5f };
	worldTransform7_.scale_ = { 12.0f,1.0f,12.0f };

	affine::makeMatIdentity(worldTransform7_.matWorld_);
	affine::makeMatTrans(worldTransform7_.matWorld_, worldTransform7_.translation_);
	affine::makeMatScale(worldTransform7_.matWorld_, worldTransform7_.scale_);

	for (int i = 0; i < 50; i++)
	{
		worldTransform_[i].Initialize();
		worldTransform2_[i].Initialize();
		worldTransform3_[i].Initialize();
		worldTransform4_[i].Initialize();
		worldTransform5_[i].Initialize();
		worldTransform6_[i].Initialize();

		worldTransform2_[i].rotation_ = { 0.0f,30.0f * affine::Deg2Rad,0.0f };
		worldTransform3_[i].rotation_ = { 0.0f,150.0f * affine::Deg2Rad,0.0f };
		worldTransform4_[i].rotation_ = { 0.0f,180.0f * affine::Deg2Rad,0.0f };
		worldTransform5_[i].rotation_ = { 0.0f,210.0f * affine::Deg2Rad,0.0f };
		worldTransform6_[i].rotation_ = { 0.0f,330.0f * affine::Deg2Rad,0.0f };

		worldTransform_[i].translation_ = { 0.0f,-3.0f,i * 15 + 7.0f };
		worldTransform2_[i].translation_ = { vector.x * 15 * i + vector.x * 7,-3.0f,float(vector.z * 15 * i + vector.z * 7 + 750) };
		worldTransform3_[i].translation_ = { vector.x * 750 * 2 - vector.x * i * 15 - vector.x * 7,-3.0f,float(vector.z * 15 * i + vector.z * 7 + 750) };
		worldTransform4_[i].translation_ = { vector.x * 750 * 2,-3.0f,i * 15 + 7.0f };
		worldTransform5_[i].translation_ = { vector.x * 750 * 2 - vector.x * 15 * i - vector.x * 7,-3.0f,float(-vector.z * 15 * i - vector.z * 7 ) };
		worldTransform6_[i].translation_ = { vector.x * 15 * i + vector.x * 7,-3.0f,float(-vector.z * 15 * i + -vector.z * 7) };

		affine::makeMatIdentity(worldTransform_[i].matWorld_);
		affine::makeMatIdentity(worldTransform2_[i].matWorld_);
		affine::makeMatIdentity(worldTransform3_[i].matWorld_);
		affine::makeMatIdentity(worldTransform4_[i].matWorld_);
		affine::makeMatIdentity(worldTransform5_[i].matWorld_);
		affine::makeMatIdentity(worldTransform6_[i].matWorld_);

		affine::makeMatRot(worldTransform2_[i].matWorld_, worldTransform2_[i].rotation_);
		affine::makeMatRot(worldTransform3_[i].matWorld_, worldTransform3_[i].rotation_);
		affine::makeMatRot(worldTransform4_[i].matWorld_, worldTransform4_[i].rotation_);
		affine::makeMatRot(worldTransform5_[i].matWorld_, worldTransform5_[i].rotation_);
		affine::makeMatRot(worldTransform6_[i].matWorld_, worldTransform6_[i].rotation_);

		affine::makeMatTrans(worldTransform_[i].matWorld_, worldTransform_[i].translation_);
		affine::makeMatTrans(worldTransform2_[i].matWorld_, worldTransform2_[i].translation_);
		affine::makeMatTrans(worldTransform3_[i].matWorld_, worldTransform3_[i].translation_);
		affine::makeMatTrans(worldTransform4_[i].matWorld_, worldTransform4_[i].translation_);
		affine::makeMatTrans(worldTransform5_[i].matWorld_, worldTransform5_[i].translation_);
		affine::makeMatTrans(worldTransform6_[i].matWorld_, worldTransform6_[i].translation_);

		worldTransform_[i].TransferMatrix();
		worldTransform2_[i].TransferMatrix();
		worldTransform3_[i].TransferMatrix();
		worldTransform4_[i].TransferMatrix();
		worldTransform5_[i].TransferMatrix();
		worldTransform6_[i].TransferMatrix();
	}
	worldTransform7_.TransferMatrix();

}

void stage::Update()
{
}

void stage::Draw(ViewProjection* viewProjection)
{
	stage_->Draw(worldTransform7_, *viewProjection);

	for (int i = 0; i < 50; i++)
	{
		model_->Draw(worldTransform_[i], *viewProjection);
		model_->Draw(worldTransform2_[i], *viewProjection);
		model_->Draw(worldTransform3_[i], *viewProjection);
		model_->Draw(worldTransform4_[i], *viewProjection);
		model_->Draw(worldTransform5_[i], *viewProjection);
		model_->Draw(worldTransform6_[i], *viewProjection);
	}
}
