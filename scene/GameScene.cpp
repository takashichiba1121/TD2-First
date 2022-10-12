﻿#include "GameScene.h"
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
	player_->Initialize(railCamera_->GetWorldTransformPtr());
	railCamera_->Initialize({ 0,5.0f,0.0f }, { 0,0 ,0 });
	stage_->Initialize();
	modelSkydome_->Initialize();
	door_->Initialize();

	Vector3 start = { 0.0f,0.0f,0.0f };
	Vector3 gole = { 7.5f,0.0f,static_cast<float> (7.5 * sqrt(3)) };
	vector = { gole.x - start.x,gole.y - start.y,gole.z - start.z };
	float len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len != 0)
	{
		vector /= len;
	}
	vector /= 2.0f;
}

void GameScene::Update()
{

	using namespace MathUtility;

	player_->Update();

	door_->Update();

	Vector3 player = affine::GetWorldTrans(player_->GetWorldTransform().matWorld_);

	if (player.z < 732.5f)
	{
		Vector3 move = { 0,0,0.5f };
		railCamera_->addtranslation(move);
	}
	else if (player.z == 732.5f)
	{
		Vector3 Rot = { 0,30 * affine::Deg2Rad,0 };
		Vector3 move = { 0,0,0 };
		move.x = player.x + cosf(Rot.x - affine::PIHalf);
		move.y = player.y + cosf(Rot.y - affine::PIHalf);
		move.z = player.z - sinf(Rot.z - affine::PIHalf);
		move -= railCamera_->GetWorldTransformPtr()->translation_;
		float len = sqrt(move.x * move.x + move.y * move.y + move.z * move.z);
		if (len != 0)
		{
			move /= len;
		}
		railCamera_->addRot(Rot);
		railCamera_->addtranslation({ move.x,move.y,move.z });
	}
	else if (player.z >= 732.5f)
	{
		railCamera_->addtranslation({ vector });
	}

	railCamera_->Update(player_->GetWorldTransform());

	debugText_->SetPos(10, 10);
	debugText_->Printf(" %f, %f, %f", player.x, player.y, player.z);
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
