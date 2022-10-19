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
	stage_ = std::make_unique<stage>();
	modelSkydome_ = std::make_unique<sky>();
	door_ = std::make_unique<door>();
	particle_ = std::make_unique<Particle>();
	resultCamera_ = std::make_unique<ResultCamera>();

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	player_->Initialize(railCamera_->GetWorldTransformPtr());
	railCamera_->Initialize(Vector3{ 0.0,0.0f,-10.0f }, { 0,0,0 });
	stage_->Initialize();
	modelSkydome_->Initialize();
	door_->Initialize();
	particle_->Initialize();
	resultCamera_->Initialize(railCamera_->GetWorldTransformPtr());
	objectManager_ = std::make_unique<ObjectManager>();
	objectManager_->Initialize(player_.get());

	/*PrimitiveDrawer::GetInstance()->SetViewProjection(railCamera_->GetViewProjection());*/
}

void GameScene::Update()
{

	using namespace MathUtility;

	door_->Update();

	railCamera_->Update(player_->GetCrashFlag());

	player_->Update();

	resultCamera_->Update();

	objectManager_->Update();

	/*debugText_->SetPos(10, 10);
	debugText_->Printf(" %f, %f, %f", player.x, player.y, player.z);
	debugText_->SetPos(10, 30);
	debugText_->Printf(" %d", spped);
	debugText_->SetPos(10, 50);
	debugText_->Printf(" %d", currentSide);*/
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
	objectManager_->Draw(railCamera_->GetViewProjection());
	stage_->Draw(railCamera_->GetViewProjection());
	modelSkydome_->Draw(railCamera_->GetViewProjection());

	/*player_->GetCollider().DebugDraw();*/

	/*objectManager_->DebugDraw();*/
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	particle_->Draw();


	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
