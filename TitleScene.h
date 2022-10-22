#pragma once
#include"Sprite.h"
#include "TextureManager.h"
#include<memory>

class TitleScene
{
public:
	/// <summary>
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
	void SpriteDraw();
private:
	std::unique_ptr<Sprite> sprite_;
	uint32_t textureHandle_ = 0;
};

