#pragma once

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
#include "Particle.h"

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
	std::unique_ptr<Particle> particle_;

	Vector3 vector={0,0,0};
	Vector3 playerVector={0,0,0};
	float kyori = 0;
	float rotRange[6] = {};

	int spped=1;

	enum class side {
		First=1,//一番
		Second,//二番
		Third,//三番
		Fourth,//四番
		Fifth,//五番
		Sixth//六番
	};

	side currentSide=side::First;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
