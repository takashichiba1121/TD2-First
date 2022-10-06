#include "door.h"

door::door()
{
}

door::~door()
{
}

void door::Initialize()
{
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
	}

	// デバック文字
	debugText_->SetPos(50, 20);
	debugText_->GetInstance()->Printf("mashNum(%d)",mashNum_);
}

void door::Update()
{
	Mash();
}

void door::Draw()
{
}
