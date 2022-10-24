#include "TitleScene.h"

void TitleScene::Initialize()
{
	textureHandle_ = TextureManager::Load("Rin.png");
	pushSpaceHandle_ = TextureManager::Load("PushSpace.png");
	sprite_.reset(Sprite::Create(textureHandle_, { 700,130 }));
	spriteSpace_.reset(Sprite::Create(pushSpaceHandle_, { 490,580 }));
}

void TitleScene::SpriteDraw()
{
	sprite_->Draw();
	spriteSpace_->Draw();
}
