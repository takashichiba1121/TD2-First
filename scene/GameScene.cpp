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
	using namespace MathUtility;

	player_ = std::make_unique<Player>();
	railCamera_ = std::make_unique<RailCamera>();
	resultCamera_ = std::make_unique<ResultCamera>();
	stage_ = std::make_unique<stage>();
	modelSkydome_ = std::make_unique<sky>();
	door_ = std::make_unique<door>();
	particle_ = std::make_unique<Particle>();
	objectManager_ = std::make_unique<ObjectManager>();
	titleScene_ = std::make_unique<TitleScene>();
	resultScene_ = std::make_unique<ResultScene>();

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	player_->Initialize(railCamera_->GetWorldTransformPtr());
	railCamera_->Initialize(Vector3{ 0.0,0.0f,-10.0f }, { 0,0,0 });
	resultCamera_->Initialize(railCamera_->GetWorldTransformPtr());
	stage_->Initialize();
	modelSkydome_->Initialize();
	door_->Initialize();
	particle_->Initialize();
	objectManager_->Initialize(player_.get());
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
		railCamera_->Update(player_->GetCrashFlag());
		resultCamera_->Update();
		player_->titleUpdate();
		titleScene_->Update();
		if (input_->TriggerKey(DIK_Q)) {
			scene = Scene::game;
			viewProjection = railCamera_->GetViewProjection();
			railCamera_->reset();
		}
		break;
	case Scene::game:
		if (railCamera_->Update(player_->GetCrashFlag()))
		{
			scene = Scene::door;
		}
		player_->Update();
		objectManager_->Update();
		speedUpChance_->Update(player_.get());
		if (input_->TriggerKey(DIK_Q)) {
			viewProjection = resultCamera_->GetViewProjection();
			scene = Scene::result;
		}
		break;
	case Scene::door:
		door_->Update();
		/*player_->titleUpdate();*/
		if (door_->GetMashFlag()) {
			scene = Scene::game;
			door_->ResetMashFlag();
		}
		break;
	case Scene::result:
		railCamera_->Update(player_->GetCrashFlag());
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
		door_->Draw(viewProjection);
		break;
	case GameScene::Scene::door:
		door_->Draw(viewProjection);
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
		break;
	case GameScene::Scene::door:
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
