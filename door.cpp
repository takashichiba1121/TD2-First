#include "door.h"

door::door()
{
}

door::~door()
{
}

void door::Initialize()
{
	input_.reset(Input::GetInstance());
	debugText_.reset(DebugText::GetInstance());
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

	if (input_->PushKey(DIK_SPACE))
	{
		mashNum_++;
	}
	if (mashNum_ > 10)
	{
		mashNum_ == 0;
	}

	// デバック文字
	debugText_->SetPos(50, 20);
	debugText_->GetInstance()->Printf("Player(%d)",mashNum_);
}

void door::Update()
{
	Mash();
}

void door::Draw()
{
}
