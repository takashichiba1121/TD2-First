#include "ResultScene.h"

void ResultScene::Initialize()
{
	spriteSpace_ = std::make_unique<Sprite>();

	pushSpaceHandle_ = TextureManager::Load("PushSpace.png");


	spriteSpace_.reset(Sprite::Create(pushSpaceHandle_, { 490,580 }));
}

void ResultScene::Update()
{
}

void ResultScene::SpriteDraw()
{
	spriteSpace_->Draw();
}
