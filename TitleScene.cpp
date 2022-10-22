#include "TitleScene.h"

void TitleScene::Initialize()
{
	textureHandle_ = TextureManager::Load("Rin.png");
}

void TitleScene::Update()
{
	sprite_.reset(Sprite::Create(textureHandle_, { 700,90 }));
}

void TitleScene::SpriteDraw()
{
	sprite_->Draw();
}
