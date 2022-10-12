#include "Particle.h"

Hexagon num;

void Particle::Initilize()
{
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Hexagon.png");
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	pos.x = 0;
	pos.y = -48;

	oldpos.x = 150;
	oldpos.y = -48;
}

void Particle::EyeCatch()
{
	if (input_->TriggerKey(DIK_P))
	{
		flag = true;
	}

	// ウィンドウサイズを超えたら
	if (pos.x > 1400)
	{
		if (flag2 == true)
		{
			pos.x = 0;
			pos.y += 48;
			flag2 = false;
		}
		else
		{
			pos.x = -75;
			pos.y += 48;
			flag2 = true;
		}
	}
	if (oldpos.x > 1400)
	{
		if (flag3 == true)
		{
			oldpos.x = 150;
			oldpos.y += 48;
			flag3 = false;
		}
		else
		{
			oldpos.x = 75;
			oldpos.y += 48;
			flag3 = true;
		}
	}
	
	if (flag == true)
	{
		Hexagon tmp;
		Hexagon tmp2;
		tmp.sprite_.reset(Sprite::Create(textureHandle_, { pos.x,pos.y }));
		tmp2.sprite_.reset(Sprite::Create(textureHandle_, {oldpos.x,oldpos.y }));
		sprite_.push_back(std::move(tmp));
		sprite_2.push_back(std::move(tmp2));
		
		sprite_.remove_if([](Hexagon& hexagon)
			{
				return hexagon.timer <= 0;
			});
		sprite_2.remove_if([](Hexagon& hexagon)
			{
				return hexagon.timer <= 0;
			});

		for (Hexagon& i : sprite_)
		{
			i.sprite_->Draw();
			i.timer--;
		}
		for (Hexagon& j : sprite_2)
		{
			j.sprite_->Draw();
			j.timer--;
		}

		pos.x += 300;
		oldpos.x += 300;
		num.timer++;
	}
	if (num.timer > 330)
	{
		flag = false;
	}
}


void Particle::Update()
{
	//EyeCatch();
	// デバック文字
	debugText_->SetPos(50, 40);
	debugText_->GetInstance()->Printf("x,y,oldx,oldy((%f,%f,(%f)))", pos.x, pos.y,num.timer);
}

void Particle::Draw()
{
	EyeCatch();
}