#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<time.h>

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	using namespace MathUtility;

	player_ = std::make_unique<Player>();
	railCamera_ = std::make_unique<RailCamera>();
	resultCamera_ = std::make_unique<ResultCamera>();
	stage_ = std::make_unique<stage>();
	modelSkydome_ = std::make_unique<sky>();
	particle_ = std::make_unique<Particle>();
	objectManager_ = std::make_unique<ObjectManager>();
	titleScene_ = std::make_unique<TitleScene>();
	resultScene_ = std::make_unique<ResultScene>();
	doorManager_ = std::make_unique<DoorManager>();

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	player_->Initialize(railCamera_->GetWorldTransformPtr());
	railCamera_->Initialize(Vector3{ 0.0,0.0f,-10.0f }, { 0,0,0 });
	resultCamera_->Initialize(railCamera_->GetWorldTransformPtr());
	stage_->Initialize();
	modelSkydome_->Initialize();
	particle_->Initialize();
	objectManager_->Initialize(player_.get());
	doorManager_->Initialize(railCamera_->GetVector());
	titleScene_->Initialize();
	resultScene_->Initialize();
	speedUpChance_ = std::make_unique<SpeedUpChance>();
	speedUpChance_->Initialize(railCamera_.get());
	PrimitiveDrawer::GetInstance()->SetViewProjection(railCamera_->GetViewProjection());
	viewProjection = resultCamera_->GetViewProjection();
}

void GameScene::Update()
{
	switch (scene)
	{
	case Scene::title:
		railCamera_->Update(player_->GetCrashFlag(), frequencyInvocationDoor);
		resultCamera_->Update();
		player_->titleUpdate();
		if (input_->TriggerKey(DIK_Q)) {
			scene = Scene::game;
			viewProjection = railCamera_->GetViewProjection();
			railCamera_->reset();
			stateTime = time(NULL);
		}
		break;
	case Scene::game:
		if (isActivationDoor==false)
		{
			if (railCamera_->Update(player_->GetCrashFlag(), frequencyInvocationDoor))
			{
				player_->SetTransform({ 0.0f, -2.0f, 10.0f });
				isActivationDoor = true;
				frequencyInvocationDoor++;
			}
			player_->Update();
			objectManager_->Update();
			speedUpChance_->Update(player_.get());
			if (input_->TriggerKey(DIK_Q)) {
				viewProjection = resultCamera_->GetViewProjection();

				endTime = nowTime;

				scene = Scene::result;
			}
			if (railCamera_->GetIsRapReset())
			{
				railCamera_->lapReset();
				doorManager_->Reset();
				frequencyInvocationDoor = 0;
			}
		}
		else
		{
			doorManager_->Update(frequencyInvocationDoor);
			if (doorManager_->GetMashFlag(frequencyInvocationDoor)) {
				isActivationDoor = false;
			}
		}
		nowTime = time(NULL) - stateTime;
		break;
	case Scene::result:
		railCamera_->Update(player_->GetCrashFlag(), frequencyInvocationDoor);
		player_->titleUpdate();
		resultCamera_->Update();
		resultScene_->Update();
		if (input_->TriggerKey(DIK_Q)) {
			scene = Scene::title;
		}
		break;
	default:
		break;
	}

	debugText_->SetPos(10, 100);
	debugText_->Printf(" %f",affine::GetWorldTrans(player_->GetWorldTransform().matWorld_).x);

	debugText_->SetPos(10, 120);
	debugText_->Printf("time::%d,%d", nowTime / 60, nowTime % 60);
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
	switch (scene)
	{
	case GameScene::Scene::title:
		break;
	case GameScene::Scene::game:
		objectManager_->Draw(viewProjection);
		speedUpChance_->Draw(viewProjection);
		doorManager_->Draw(viewProjection);
		break;
	case GameScene::Scene::result:
		break;
	default:
		break;
	}
	player_->Draw(viewProjection);
	stage_->Draw(viewProjection);
	modelSkydome_->Draw(viewProjection);

	player_->GetCollider().DebugDraw();
	objectManager_->DebugDraw();
	speedUpChance_->DebugDraw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	switch (scene)
	{
	case GameScene::Scene::title:
		titleScene_->SpriteDraw();
		break;
	case GameScene::Scene::game:
		
		if (isActivationDoor)
		{
			doorManager_->SpriteDraw();
		}
		break;
	case GameScene::Scene::result:
		resultScene_->SpriteDraw();
		break;
	default:
		break;
	}
	/// </summary>
	particle_->Draw();


	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
