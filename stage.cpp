#include "stage.h"

stage::stage()
{
}

stage::~stage()
{
}

void stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();
	worldTransform2_.Initialize();

	worldTransform_.scale_ = {};
}

void stage::Update()
{
}

void stage::Draw()
{
}
