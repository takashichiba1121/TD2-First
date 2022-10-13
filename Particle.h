#pragma once
#include "Sprite.h"
#include "Input.h"
#include "DebugText.h"
#include <list>
#include "TextureManager.h"
#include "WorldTransform.h"

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
	void Initialize();

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

	/// <summary>
	/// �l�̏�����
	/// </summary>
	void Reset();

	Vector2 pos;
	Vector2 pos2;
	Vector2 bottom;

	bool flag = false;
	bool flag2 = false;
	bool flag3 = false;
private:
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;
	uint32_t textureBox_ = 0;
	// �X�v���C�g
	std::list<Hexagon> sprite_;
	std::list<Hexagon> sprite_2;
	std::unique_ptr<Sprite> spriteBox_;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

