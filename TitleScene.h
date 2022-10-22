#pragma once
#include"Sprite.h"
#include "TextureManager.h"
#include<memory>

class TitleScene
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void SpriteDraw();
private:
	std::unique_ptr<Sprite> sprite_;
	uint32_t textureHandle_ = 0;
};

