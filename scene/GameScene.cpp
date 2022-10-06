#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	player_ = std::make_unique<Player>();
	railCamera_ = std::make_unique<RailCamera>();
	stage_ = std::make_unique<stage>();
	modelSkydome_ = std::make_unique<sky>();
	door_ = std::make_unique<door>();

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	player_->Initialize();
	railCamera_->Initialize({ 0,0.7f,0.0f }, { 0,0 ,45.0f * affine::Deg2Rad });
	stage_->Initialize();
	modelSkydome_->Initialize();
	door_->Initialize();
}

void GameScene::Update()
{

	player_->Update();

	door_->Update();

	Vector3 move = { 0,0,0 };
	railCamera_->Update(move, move);
}

void GameScene::Draw()
{

// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player_->Draw(railCamera_->GetViewProjection());
	stage_->Draw(railCamera_->GetViewProjection());
	modelSkydome_->Draw(railCamera_->GetViewProjection());
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
