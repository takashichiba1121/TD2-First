#include "ObjectManager.h"

void ObjectManager::Initialize(Player* player)
{
	player_ = player;

	std::unique_ptr<Object> object;

	object = std::make_unique<Object>();
	object->Initialize({ 0, -1.5, 200 }, 1.0f, Model::Create());

	objects_.push_back(std::move(object));
}

void ObjectManager::Update()
{
	objects_.remove_if([](std::unique_ptr<Object>& call)
		{
			return call->GetIsDeath();
		});

	for (std::unique_ptr<Object>& object : objects_)
	{
		object->Update();
	
		if (CheckAABB2SPHERE(player_->GetCollider(),object->GetCollider()))
		{
			object->OnCollision();
			player_->OnCollision();
		}
	}
}

void ObjectManager::Draw(ViewProjection* ViewProjection)
{
	for (std::unique_ptr<Object>& object : objects_)
	{
		object->Draw(ViewProjection);
	}
}


void ObjectManager::DebugDraw()
{
	for (std::unique_ptr<Object>& object : objects_)
	{
		//object->GetCollider().DebugDraw();
	}
}