#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "affine.h"
#include <memory>

class Goal
{
public:
	// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize();

	// <summary>
	/// ï`âÊ
	/// </summary>
	void Draw(ViewProjection* viewProjection);

private:
	std::unique_ptr<Model> model_;
	std::unique_ptr<WorldTransform> worldTransform_;
};