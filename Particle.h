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
	/// 初期化
	/// </summary>
	void Initilize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// アイキャッチ
	/// </summary>
	void EyeCatch();

	Vector2 pos;
	Vector2 oldpos;
	bool flag = false;
	bool flag2 = false;
	bool flag3 = false;
private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// スプライト
	std::list<Hexagon> sprite_;
	std::list<Hexagon> sprite_2;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	int a;
};

