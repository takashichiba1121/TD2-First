#include "Door.h"

door::door()
{
}

door::~door()
{
}

void door::Initialize()
{
	worldTransform_.Initialize();
	//model_.reset(Model::CreateFromOBJ("   ", true));
	input_=Input::GetInstance();
	debugText_ = DebugText::GetInstance();
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
