#include "DoorManager.h"
#include"affine.h"

void DoorManager::Initialize(Vector3 vector)
{
	vector_ = vector;

	door_[0] = std::make_unique<door>();
	door_[1] = std::make_unique<door>();
	door_[2] = std::make_unique<door>();
	door_[3] = std::make_unique<door>();

	door_[0]->Initialize(Vector3(375 * vector_.x, 4.0f, 750 + 375 * vector_.z), Vector3(0.0f, 30.0f * affine::Deg2Rad, 0.0f));
	door_[1]->Initialize(Vector3(600 * vector_.x, 4.0f, 600 * -vector_.z), Vector3(0.0f, 330.0f * affine::Deg2Rad, 0.0f));
	door_[2]->Initialize(Vector3(450 * vector_.x, 4.0f, 450 * -vector_.z), Vector3(0.0f, 330.0f * affine::Deg2Rad, 0.0f));
	door_[3]->Initialize(Vector3(300 * vector_.x, 4.0f, 300 * -vector_.z), Vector3(0.0f, 330.0f * affine::Deg2Rad, 0.0f));


	textureHandle_ = TextureManager::Load("MashSpace.png");
	sprite_.reset(Sprite::Create(textureHandle_, { 440,480 }));
}

void DoorManager::Update(int frequencyInvocationDoor)
{
	if (frequencyInvocationDoor == 1)
	{
		door_[frequencyInvocationDoor-1]->Update();
	}
	if (frequencyInvocationDoor == 2)
	{
		door_[frequencyInvocationDoor-1]->Update();
	}
	if (frequencyInvocationDoor == 3)
	{
		door_[frequencyInvocationDoor-1]->Update();
	}
	if (frequencyInvocationDoor == 4)
	{
		door_[frequencyInvocationDoor-1]->Update();
	}
}

void DoorManager::Draw(ViewProjection* ViewProjection)
{
	for (int i = 0; i < 4; i++)
	{
		door_[i]->Draw(ViewProjection);
	}
}
void DoorManager::SpriteDraw()
{
	sprite_->Draw();
}

void DoorManager::Reset()
{
	door_[0]->Reset(Vector3(375 * vector_.x, 4.0f, 750 + 375 * vector_.z));
}

bool DoorManager::GetMashFlag(int frequencyInvocationDoor)
{
	return door_[frequencyInvocationDoor-1]->GetMashFlag();
}
