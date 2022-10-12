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
	 vector[0] = {gole.x - start.x,gole.y - start.y,gole.z - start.z};
	float len = sqrt(vector[0].x * vector[0].x + vector[0].y * vector[0].y + vector[0].z * vector[0].z);
	if (len != 0)
	{
		vector[0] /= len;
	}

	for (int i = 0; i < 50; i++)
	{
		worldTransform_[i].Initialize();
		worldTransform2_[i].Initialize();

		worldTransform2_[i].rotation_ = {0.0f,30.0f * affine::Deg2Rad,0.0f};

		worldTransform_[i].translation_ = { 0.0f,-3.0f,i*15+7.0f };
		worldTransform2_[i].translation_ = { vector[0].x * 15 * i + vector[0].x * 7,-3.0f,float(vector[0].z * 15 * i + vector[0].z * 7 + 745.9)};

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
