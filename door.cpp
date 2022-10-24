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
	door2worldTransform_.Initialize();
	door3worldTransform_.Initialize();
	door2model_.reset(Model::CreateFromOBJ("door2", true));
	door3model_.reset(Model::CreateFromOBJ("door3", true));
	input_=Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	door2worldTransform_.translation_ = {741.5f,4.0f,355.0f};
	door3worldTransform_.translation_ = { 758.5f,4.0f,355.0f };

	door2worldTransform_.scale_ = { 10.0f,10.0f,1.0f };
	door3worldTransform_.scale_ = { 10.0f,10.0f,1.0f };

	door2worldTransform_.rotation_ = {0.0f,180.0f*affine::Deg2Rad,0.0f};
	door3worldTransform_.rotation_ = { 0.0f,180.0f * affine::Deg2Rad,0.0f };

	affine::makeAffine(door2worldTransform_);
	affine::makeAffine(door3worldTransform_);

	door2worldTransform_.TransferMatrix();
	door3worldTransform_.TransferMatrix();
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
		door2worldTransform_.translation_.x = 740.0f;
		door3worldTransform_.translation_.x = 760.0f;
	}

	// デバック文字
	debugText_->SetPos(50, 20);
	debugText_->GetInstance()->Printf("MashNum(%d)",mashNum_);
}

void door::Update()
{
	Mash();

	affine::makeAffine(door2worldTransform_);
	affine::makeAffine(door3worldTransform_);

	door2worldTransform_.TransferMatrix();
	door3worldTransform_.TransferMatrix();
}

void door::Draw(ViewProjection*viewProjection)
{
	door2model_->Draw(door2worldTransform_, *viewProjection);
	door3model_->Draw(door3worldTransform_, *viewProjection);
}

void door::Reset()
{
	mashFlag_ = false;
	door2worldTransform_.translation_.x = 741.5f;
	door3worldTransform_.translation_.x = 758.5f;

	affine::makeAffine(door2worldTransform_);
	affine::makeAffine(door3worldTransform_);

	door2worldTransform_.TransferMatrix();
	door3worldTransform_.TransferMatrix();
}
