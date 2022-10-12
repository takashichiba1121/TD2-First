#pragma once
#include"Object.h"
#include"affine.h"

class ObjectManager
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WorldTransform* playerWorldTransform);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* ViewProjection);

private:

	std::list<std::unique_ptr<Object>>objects_;
	WorldTransform* playerWorldTransform_;
};

