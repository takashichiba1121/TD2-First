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

	Vector3 start = { 0.0f,0.0f,0.0f };
	Vector3 gole = { 7.5f,0.0f,static_cast<float> (7.5 * sqrt(3)) };
	vector = { gole.x - start.x,gole.y - start.y,gole.z - start.z };
	float len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len != 0)
	{
		vector /= len;
	}

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
		/*worldTransform4_[i].rotation_ = { 0.0f,90.0f * affine::Deg2Rad,0.0f };
		worldTransform5_[i].rotation_ = { 0.0f,120.0f * affine::Deg2Rad,0.0f };
		worldTransform6_[i].rotation_ = { 0.0f,150.0f * affine::Deg2Rad,0.0f };*/

		worldTransform_[i].translation_ = { 0.0f,-3.0f,i * 15 + 7.0f };
		worldTransform2_[i].translation_ = { vector.x * 15 * i + vector.x * 7,-3.0f,float(vector.z * 15 * i + vector.z * 7 + 750) };
		worldTransform3_[i].translation_ = { vector.x*750*2-vector.x*i*15,-3.0f,float(vector.z * 15 * i + vector.z * 7 + 745.9) };
		/*worldTransform4_[i].translation_ = { vector[2].x * 15 * i + vector[2].x * 7,-3.0f,float(vector[2].z * 15 * i + vector[2].z * 7 + 750) };
		worldTransform5_[i].translation_ = { vector[3].x * 15 * i + vector[3].x * 7,-3.0f,float(vector[3].z * 15 * i + vector[3].z * 7 + 745.9) };
		worldTransform6_[i].translation_ = { vector[4].x * 15 * i + vector[4].x * 7,-3.0f,float(vector[4].z * 15 * i + vector[4].z * 7 + 745.9) };*/

		affine::makeMatIdentity(worldTransform_[i].matWorld_);
		affine::makeMatIdentity(worldTransform2_[i].matWorld_);
		affine::makeMatIdentity(worldTransform3_[i].matWorld_);

		affine::makeMatRot(worldTransform2_[i].matWorld_, worldTransform2_[i].rotation_);
		affine::makeMatRot(worldTransform3_[i].matWorld_, worldTransform3_[i].rotation_);

		affine::makeMatTrans(worldTransform_[i].matWorld_, worldTransform_[i].translation_);
		affine::makeMatTrans(worldTransform2_[i].matWorld_, worldTransform2_[i].translation_);
		affine::makeMatTrans(worldTransform3_[i].matWorld_, worldTransform3_[i].translation_);

		worldTransform_[i].TransferMatrix();
		worldTransform2_[i].TransferMatrix();
		worldTransform3_[i].TransferMatrix();
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
		model_->Draw(worldTransform3_[i], *viewProjection);
	}
}
