#include "Particle.h"

Hexagon num;

void Particle::Initilize()
{
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Hexagon.png");
	textureBox_ = TextureManager::Load("white1x1.png");

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	Reset();
}

void Particle::Reset()
{
	pos.x = 0;
	pos.y = -48;

	pos2.x = 150;
	pos2.y = -48;

	bottom.y = -48;

	num.timer = 120;
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
	if (pos2.x > 1400)
	{
		if (flag3 == true)
		{
			pos2.x = 150;
			pos2.y += 48;
			flag3 = false;
		}
		else
		{
			pos2.x = 75;
			pos2.y += 48;
			flag3 = true;
		}
	}

	if (flag == true)
	{
		Hexagon tmp;
		Hexagon tmp2;
		tmp.sprite_.reset(Sprite::Create(textureHandle_, { pos.x,pos.y }));
		tmp2.sprite_.reset(Sprite::Create(textureHandle_, { pos2.x,pos2.y }));
		spriteBox_.reset(Sprite::Create(textureHandle_, {640, bottom.y }));

		sprite_.push_back(std::move(tmp));
		sprite_2.push_back(std::move(tmp2));

		spriteBox_->SetSize({ 1280.0f, bottom.y });

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
		pos2.x += 300;
		num.timer++;
		bottom.y += 10.0f;
		spriteBox_->SetPosition(bottom);
	}
	if (num.timer > 330)
	{
		flag = false;
		if (flag == false)
		{
			Reset();
		}
	}
}


void Particle::Update()
{
	//EyeCatch();
	// デバック文字
	debugText_->SetPos(50, 80);
	debugText_->GetInstance()->Printf("x,y((%f,%f))", bottom.x, bottom.y);
}

void Particle::Draw()
{
	EyeCatch();
}