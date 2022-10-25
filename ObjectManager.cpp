#include "ObjectManager.h"

void ObjectManager::Initialize(Player* player)
{
	player_ = player;

	Reset();
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

		if (CheckAABB2SPHERE(player_->GetCollider(), object->GetCollider()))
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

void ObjectManager::Reset()
{
	objects_.clear();

	std::unique_ptr<Object> object;

	//�ŏ��̓�	|
	object = std::make_unique<Object>();
	object->Initialize({ -1.5f, -1.5f, 280.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, Model::Create());

	objects_.push_back(std::move(object));

	object = std::make_unique<Object>();
	object->Initialize({ 1.5f, -1.5f, 300.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, Model::Create());

	objects_.push_back(std::move(object));

	//���ӂ���
	for (size_t i = 0; i < 10; i++)
	{
		object = std::make_unique<Object>();
		object->Initialize({ 10.0f - i * 2.0f, -1.5f, 400.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, Model::Create());

		objects_.push_back(std::move(object));
	}

	//���ӂ���
	for (size_t i = 0; i < 10; i++)
	{
		object = std::make_unique<Object>();
		object->Initialize({ 10.0f - i * 2.0f, -1.5f, 500.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, Model::Create());

		objects_.push_back(std::move(object));
	}

	//��ڂ̓�	/

	//���e�ǂ�

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (j != 3 && j != 4)
			{
				object = std::make_unique<Object>();
				object->Initialize({ 67.0f - j * 1.75f, 2.5f - 2.0f * i, 850.0f + j * 1.0f }, { 0.0f, 30.0f * affine::Deg2Rad, 0.0f }, 1.0f, Model::Create());
				objects_.push_back(std::move(object));
			}
		}
	}

	//���ӂ���
	for (size_t j = 0; j < 9; j++)
	{

			object = std::make_unique<Object>();
			object->Initialize({ 298.0f - j * 1.75f, -1.5f , 1250.0f + j * 1.0f }, { 0.0f, 30.0f * affine::Deg2Rad, 0.0f }, 1.0f, Model::Create());
			objects_.push_back(std::move(object));
	}

	//3�ڂ̓�

	//���ӂ���
	for (size_t k = 0; k < 3; k++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			for (size_t i = 0; i < 5; i++)
			{
				object = std::make_unique<Object>();
				object->Initialize({ (490.0f + i * 1.75f) + j * 1.0f, 2.5f - 2.0f * k, (1200.0f + i * 1.0f) - j * 1.75f }, { 0.0f, 60.0f * affine::Deg2Rad, 0.0f }, 1.0f, Model::Create());
				objects_.push_back(std::move(object));
			}
		}
	}

	for (size_t k = 0; k < 3; k++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			for (size_t i = 0; i < 5; i++)
			{
				object = std::make_unique<Object>();
				object->Initialize({ (653.5f + i * 1.75f) + j * 1.0f, 2.5f - 2.0f * k, (900.0f + i * 1.0f) - j * 1.75f }, { 0.0f, 60.0f * affine::Deg2Rad, 0.0f }, 1.0f, Model::Create());
				objects_.push_back(std::move(object));
			}
		}
	}

	//4�ڂ̓�

	//����
	for (size_t i = 0; i < 4; i++)
	{
		if (i != 1 && i != 2)
		{
			object = std::make_unique<Object>();
			object->Initialize({ 750.0f + i * 2.0f,-1.5f,440.3f }, { 0.0f, 0.0f, 0.0f }, 1.0f, Model::Create());

			objects_.push_back(std::move(object));
		}
		else
		{
			object = std::make_unique<Object>();
			object->Initialize({ 750.0f + i * 2.0f,0.5f,440.3f }, { 0.0f, 0.0f, 0.0f }, 1.0f, Model::Create());

			objects_.push_back(std::move(object));
		}

	}

	//����
	for (size_t i = 0; i < 4; i++)
	{
		if (i != 1 && i != 2)
		{
			object = std::make_unique<Object>();
			object->Initialize({ 744.0f + i * 2.0f,-1.5f,160.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, Model::Create());

			objects_.push_back(std::move(object));
		}
		else
		{
			object = std::make_unique<Object>();
			object->Initialize({ 744.0f + i * 2.0f,0.5f,160.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, Model::Create());

			objects_.push_back(std::move(object));
		}

	}

	//���ӂ���
	for (size_t i = 0; i < 10; i++)
	{
		object = std::make_unique<Object>();
		object->Initialize({ 740.0f + i * 2.0f, -1.5f, 70.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, Model::Create());

		objects_.push_back(std::move(object));
	}

	//5�ڂ̓�

	//����
	for (size_t i = 0; i < 8; i++)
	{
		if (i != 1 && i != 2 && i != 5 && i != 6)
		{
			object = std::make_unique<Object>();
			object->Initialize({ 699.0f - i * 1.75f, -1.5f , -100.0f + i * 1.0f }, { 0.0f, 30.0f * affine::Deg2Rad, 0.0f }, 1.0f, Model::Create());

			objects_.push_back(std::move(object));
		}
		else
		{
			object = std::make_unique<Object>();
			object->Initialize({ 699.0f - i * 1.75f, 0.5f , -100.0f + i * 1.0f }, { 0.0f, 30.0f * affine::Deg2Rad, 0.0f }, 1.0f, Model::Create());

			objects_.push_back(std::move(object));
		}

	}

	//���ӂ���
	for (size_t k = 0; k < 3; k++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			for (size_t i = 0; i < 5; i++)
			{
				object = std::make_unique<Object>();
				object->Initialize({ (586.0f - i * 1.75f) - j * 1.0f, 2.5f - 2.0f * k, (-284.0f + i * 1.0f) - j * 1.75f }, { 0.0f, 30.0f * affine::Deg2Rad, 0.0f }, 1.0f, Model::Create());
				objects_.push_back(std::move(object));
			}
		}
	}

	for (size_t k = 0; k < 3; k++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			for (size_t i = 0; i < 5; i++)
			{
				object = std::make_unique<Object>();
				object->Initialize({ (506.0f - i * 1.75f) - j * 1.0f, 2.5f - 2.0f * k, (-439.0f + i * 1.0f) - j * 1.75f }, { 0.0f, 30.0f * affine::Deg2Rad, 0.0f }, 1.0f, Model::Create());
				objects_.push_back(std::move(object));
			}
		}
	}

	//6�ڂ̓�

	//���ӂ���
	for (size_t i = 0; i < 9; i++)
	{
		object = std::make_unique<Object>();
		object->Initialize({ 50.0f + i * 1.75f, -1.5f, -100.0f  + i * 1.0f }, { 0.0f,60.0f * affine::Deg2Rad, 0.0f }, 1.0f, Model::Create());

		objects_.push_back(std::move(object));
	}
}