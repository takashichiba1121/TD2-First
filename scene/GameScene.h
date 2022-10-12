﻿#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "player.h"
#include"stage.h"
#include "RailCamera.h"

#include "sky.h"
#include "door.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	std::unique_ptr<RailCamera> railCamera_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<stage> stage_;
	std::unique_ptr<sky> modelSkydome_;
	std::unique_ptr<door> door_;

	Vector3 vector={0,0,0};
	Vector3 playerVector={0,0,0};
	float kyori = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
