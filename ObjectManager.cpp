#include "ObjectManager.h"

void ObjectManager::Initialize(WorldTransform* playerWorldTransform)
{

}


void ObjectManager::Update()
{
	for (std::unique_ptr<Object>& object : objects_)
	{
		object->Update(affine::GetWorldTrans(playerWorldTransform_->matWorld_));
	}
}

void ObjectManager::Draw(ViewProjection* ViewProjection)
{
	for (std::unique_ptr<Object>& object : objects_)
	{
		object->Draw(ViewProjection);
	}
}