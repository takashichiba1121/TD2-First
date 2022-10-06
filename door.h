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
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool mashFlag_ = false;
	UINT mashNum_ = 0;
private:

	/// <summary>
	/// 連打処理
	/// </summary>
	void Mash();

	std::unique_ptr<Input> input_ = nullptr;
	std::unique_ptr<DebugText> debugText_ = nullptr;
};

