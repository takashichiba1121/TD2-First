#pragma once
#include "Sprite.h"
#include "Input.h"
#include "DebugText.h"
#include <list>
#include "TextureManager.h"

struct Hexagon
{
	std::unique_ptr<Sprite> sprite_;
	float timer = 120;
};

class Particle
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initilize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �A�C�L���b�`
	/// </summary>
	void EyeCatch();

	Vector2 pos;
	Vector2 oldpos;
	bool flag = false;
	bool flag2 = false;
	bool flag3 = false;
private:
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;
	// �X�v���C�g
	std::list<Hexagon> sprite_;
	std::list<Hexagon> sprite_2;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	int a;
};

