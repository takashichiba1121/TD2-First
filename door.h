#pragma once

#include <memory>
#include "Input.h"
#include "DebugText.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "Model.h"

class door
{
public:
	// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(Vector3 trans,Vector3 Rot);

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update(Vector3 vector);

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	bool GetMashFlag() { return mashFlag_; }

	void Reset(Vector3 trans);

	UINT GetMashNum() { return mashNum_; }

private:

	//˜A‘Åˆ—
	void Mash(Vector3 vector);

	bool mashFlag_ = false;
	UINT mashNum_ = 0;

	WorldTransform door1worldTransform_;
	WorldTransform door2worldTransform_;
	WorldTransform door3worldTransform_;

	std::unique_ptr<Model> door1model_;
	std::unique_ptr<Model> door2model_;
	std::unique_ptr<Model> door3model_;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

