#pragma once
#include"Sprite.h"
#include "TextureManager.h"
#include<memory>
class ResultScene
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
	std::unique_ptr<Sprite> spriteSpace_;

	uint32_t pushSpaceHandle_ = 0;
};

