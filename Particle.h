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
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	///<summary>
	///パーティクルスタート
	///<summary>
	void state();
	
	/// <summary>
	/// アイキャッチ
	/// </summary>
	void EyeCatch();

	/// <summary>
	/// アイキャッチの初期化
	/// </summary>
	void EyeCatchInitialize();

	/// <summary>
	/// アイキャッチの描画
	/// </summary>
	void EyeCatchDraw();

	/// <summary>
	/// 値の初期化
	/// </summary>
	void Reset();

	float GetNumTimer();

	Vector2 pos;
	Vector2 pos2;
	Vector2 bottom;

	bool flag = false;
	bool flag2 = false;
	bool flag3 = false;
private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t textureBox_ = 0;
	// スプライト
	std::list<Hexagon> sprite_;
	std::list<Hexagon> sprite_2;
	std::unique_ptr<Sprite> spriteBox_;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

