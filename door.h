#pragma once

#include <memory>
#include "Input.h"
#include "DebugText.h"
#include "WorldTransform.h"
#include "Model.h"

class door
{
public:

	door();

	~door();

	// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	bool GetMashFlag() { return mashFlag_; }

	void Reset();

	UINT GetMashNum() { return mashNum_; }

private:

	//˜A‘Åˆ—
	void Mash();

	bool mashFlag_ = false;
	UINT mashNum_ = 0;

	WorldTransform door2worldTransform_;
	WorldTransform door3worldTransform_;

	std::unique_ptr<Model> door2model_;
	std::unique_ptr<Model> door3model_;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

