#include "ObjectManager.h"

void ObjectManager::Initialize(Player* player)
{
	player_ = player;

	std::unique_ptr<Object> tmp;

	tmp = std::make_unique<Object>();
	tmp->Initialize({ 0, -1.5, 200 }, {2,2,2}, Model::Create());

	objects_.push_back(std::move(tmp));
}


void ObjectManager::Update()
{
	objects_.remove_if([](std::unique_ptr<Object>& call)
		{
			return call->GetIsDeath();
		});

	for (std::unique_ptr<Object>& object : objects_)
	{
		object->Update(affine::GetWorldTrans(player_->GetWorldTransform().matWorld_));
	
		if (CheckAABB2AABB(player_->GetCollider(),object->GetCollider()))
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
		object->GetCollider().DebugDraw();
	}
}