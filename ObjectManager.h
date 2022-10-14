#pragma once
#include"Object.h"
#include"affine.h"
#include"MathUtility.h"
#include"player.h"


class ObjectManager
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(Player* player);

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ViewProjection* ViewProjection);

	void DebugDraw();

private:

	std::list<std::unique_ptr<Object>>objects_;
	Player* player_ = nullptr;
};

