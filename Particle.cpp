#include "Particle.h"

Hexagon num;

void Particle::Initialize()
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

	bottom.y = -970;

	num.timer = 120;
}

void Particle::EyeCatchInitialize()
{
	Hexagon tmp;
	Hexagon tmp2;
	tmp.sprite_.reset(Sprite::Create(textureHandle_, { pos.x,pos.y }));
	tmp2.sprite_.reset(Sprite::Create(textureHandle_, { pos2.x,pos2.y }));
	spriteBox_.reset(Sprite::Create(textureBox_, { 0, 320 }));

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
}

void Particle::EyeCatchDraw()
{
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
}

void Particle::state()
{
		flag = true;
}

void Particle::EyeCatch()
{

	// ウィンドウサイズを超えたら一段ずらす
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
		EyeCatchInitialize();

		spriteBox_->SetSize({ 1280.0f, 980.0f });
		bottom.y += 8.5f;
		spriteBox_->SetPosition(bottom);
		spriteBox_->Draw();

		EyeCatchDraw();
		
		pos.x += 300;
		pos2.x += 300;
		num.timer++;
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

void Particle::Draw()
{
	EyeCatch();
}

float Particle::GetNumTimer()
{
	return num.timer;
}