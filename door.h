#pragma once

#include <memory>
#include "Input.h"
#include "DebugText.h"

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
	void Draw();

	bool mashFlag_ = false;
	UINT mashNum_ = 0;
private:

	/// <summary>
	/// ˜A‘Åˆ—
	/// </summary>
	void Mash();

	std::unique_ptr<Input> input_ = nullptr;
	std::unique_ptr<DebugText> debugText_ = nullptr;
};

