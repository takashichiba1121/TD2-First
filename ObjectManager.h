#pragma once
#include"Object.h"
#include"affine.h"

class ObjectManager
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(WorldTransform* playerWorldTransform);

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ViewProjection* ViewProjection);

private:

	std::list<std::unique_ptr<Object>>objects_;
	WorldTransform* playerWorldTransform_;
};

