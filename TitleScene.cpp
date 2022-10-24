#include "TitleScene.h"

void TitleScene::Initialize()
{
	textureHandle_ = TextureManager::Load("Rin.png");
	pushSpaceHandle_ = TextureManager::Load("PushSpace.png");
}

void TitleScene::Update()
{
	sprite_.reset(Sprite::Create(textureHandle_, { 700,120 }));
	spriteSpace_.reset(Sprite::Create(pushSpaceHandle_, { 490,550 }));
}

void TitleScene::SpriteDraw()
{
	sprite_->Draw();
	spriteSpace_->Draw();
}
