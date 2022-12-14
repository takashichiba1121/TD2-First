#pragma once
#include"Sprite.h"
#include "TextureManager.h"
#include<memory>
class ResultScene
{
public:

	/// <summary>
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
	void SpriteDraw();
private:
	std::unique_ptr<Sprite> spriteSpace_;

	uint32_t pushSpaceHandle_ = 0;
};

