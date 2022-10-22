#include "Door.h"
#include"affine.h"

door::door()
{
}

door::~door()
{
}

void door::Initialize()
{
	worldTransform_.Initialize();
	model_.reset(Model::CreateFromOBJ("door", true));
	input_=Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.translation_ = {0.0f,0.0f,375.0f};

	/*worldTransform_.scale_ = { 100.0f,100.0f,1.0f };*/
	
	affine::makeAffine(worldTransform_);

	worldTransform_.TransferMatrix();
}

void door::Mash()
{
	/*if (mashFlag_ == false && mashNum_ == 0)
	{
		mashFlag_ = true;
	}*/

	/*if (mashFlag_ == true)
	{
		
	}*/

	if (input_->TriggerKey(DIK_SPACE))
	{
		mashNum_++;
	}
	if (mashNum_ > 10)
	{
		mashNum_ = 0;
		mashFlag_ = true;
	}

	// デバック文字
	debugText_->SetPos(50, 20);
	debugText_->GetInstance()->Printf("MashNum(%d)",mashNum_);
}

void door::Update()
{
	Mash();
}

void door::Draw(ViewProjection*viewProjection)
{
	model_->Draw(worldTransform_, *viewProjection);
}
