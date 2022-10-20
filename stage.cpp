#include "stage.h"
#include"affine.h"
#include<cmath>
#include"MathUtility.h"

stage::stage()
{
}

stage::~stage()
{
	//delete model_;
	delete stage_;
}

void stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	stage_ = Model::CreateFromOBJ("stage", true);


	stageWorldTransform_.Initialize();
	stageWorldTransform_.translation_ = { 375.25f,-3.0f,375.25f };
	stageWorldTransform_.scale_ = { 12.0f,1.0f,12.0f };

	affine::makeAffine(stageWorldTransform_);
	
	stageWorldTransform_.TransferMatrix();

}

void stage::Update()
{
}

void stage::Draw(ViewProjection* viewProjection)
{
	stage_->Draw(stageWorldTransform_, *viewProjection);

}
