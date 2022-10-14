#pragma once
#include"Object.h"
#include"affine.h"
#include"MathUtility.h"
#include"player.h"


class ObjectManager
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Player* player);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* ViewProjection);

	void DebugDraw();

private:

	std::list<std::unique_ptr<Object>>objects_;
	Player* player_ = nullptr;
};

