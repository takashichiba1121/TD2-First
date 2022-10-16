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
	Vector3 start = { 0.0f,0.0f,0.0f };
	Vector3 gole = { 7.5f,0.0f,static_cast<float> (7.5 * sqrt(3)) };
	vector = { gole.x - start.x,gole.y - start.y,gole.z - start.z };
	float len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len != 0)
	{
		vector /= len;
	}

	rotRange[0] = 750.0f;
	rotRange[1] = rotRange[0] + vector.z * 750;
	rotRange[2] = 750.0f;
	rotRange[3] = 0.0f;
	rotRange[4] = rotRange[3] - vector.z * 750;
	rotRange[5] = 0.0f;

	/*railCamera_->addtranslation({ -4,0,7 });*/
	PrimitiveDrawer::GetInstance()->SetViewProjection(railCamera_->GetViewProjection());
}

void GameScene::Update()
{

	using namespace MathUtility;

	door_->Update();

	Vector3 player = affine::GetWorldTrans(player_->GetWorldTransform().matWorld_);

	if (input_->TriggerKey(DIK_1))
	{
		spped = 1;
	}
	if (input_->TriggerKey(DIK_2))
	{
		spped = 2;
	}
	if (input_->TriggerKey(DIK_3))
	{
		spped = 3;
	}
	if (input_->TriggerKey(DIK_4))
	{
		spped = 4;
	}
	if (input_->TriggerKey(DIK_5))
	{
		spped = 5;
	}

	switch (currentSide)
	{
	case side::First:
		if (player.z < rotRange[0])
		{
			Vector3 move = { 0,0,1.0f * spped };
			railCamera_->addTranslation(move);
		}
		else if (player.z >= rotRange[0])
		{
			Vector3 Rot = { 0,30 * affine::Deg2Rad,0 };
			/*Vector3 move = { 0,0,0 };
			move.x = player.x + cosf(Rot.y - affine::PIHalf);
			move.z = player.z - sinf(Rot.y - affine::PIHalf);
			move -= railCamera_->GetWorldTransformPtr()->translation_;
			float len = sqrt(move.x * move.x + move.y * move.y + move.z * move.z);
			if (len != 0)
			{
				move /= len;
			}*/
			railCamera_->addRot(Rot);
			railCamera_->setTranslation({ -vector.x * 10,0.0f,-vector.z * 10 + 750 });

			currentSide = side::Second;
		}
		break;
	case side::Second:
		if (player.z < rotRange[1]/* - vector.z * 10*/)
		{
			Vector3 move = { vector * spped };
			railCamera_->addTranslation({ move });
		}
		else if (player.z >= rotRange[1]/* - vector.z * 10*/)
		{
			Vector3 Rot = { 0,120 * affine::Deg2Rad,0 };
			/*Vector3 move = { 0,0,0 };
			move.x = player.x + cosf(Rot.y - affine::PIHalf);
			move.z = player.z - sinf(Rot.y - affine::PIHalf);
			move -= railCamera_->GetWorldTransformPtr()->translation_;
			float len = sqrt(move.x * move.x + move.y * move.y + move.z * move.z);
			if (len != 0)
			{
				move /= len;
			}*/
			railCamera_->addRot(Rot);
			railCamera_->setTranslation({ vector.x * 750 - vector.x * 10,0.0f,rotRange[1] + vector.z * 10 });
			currentSide = side::Third;
		}
		break;
	case side::Third:
		if (player.z > rotRange[2])
		{
			Vector3 move = { vector.x * spped,vector.y * spped,-vector.z * spped };
			railCamera_->addTranslation({ move });
		}
		else if (player.z <= rotRange[2])
		{
			Vector3 Rot = { 0,30 * affine::Deg2Rad,0 };
			/*Vector3 move = { 0,0,0 };
			move.x = player.x + cosf(Rot.y - affine::PIHalf);
			move.z = player.z - sinf(Rot.y - affine::PIHalf);
			move -= railCamera_->GetWorldTransformPtr()->translation_;
			float len = sqrt(move.x * move.x + move.y * move.y + move.z * move.z);
			if (len != 0)
			{
				move /= len;
			}*/
			railCamera_->addRot(Rot);
			railCamera_->setTranslation({ vector.x * 750 * 2,0.0f,750 + 10 });

			currentSide = side::Fourth;
		}
		break;
	case side::Fourth:
		if (player.z > rotRange[3])
		{
			Vector3 move = { 0,0,-1.0f * spped };
			railCamera_->addTranslation(move);
		}
		if (player.z <= rotRange[3])
		{
			Vector3 Rot = { 0,30 * affine::Deg2Rad,0 };
			/*Vector3 move = { 0,0,0 };
			move.x = player.x + cosf(Rot.y - affine::PIHalf);
			move.z = player.z - sinf(Rot.y - affine::PIHalf);
			move -= railCamera_->GetWorldTransformPtr()->translation_;
			float len = sqrt(move.x * move.x + move.y * move.y + move.z * move.z);
			if (len != 0)
			{
				move /= len;
			}*/
			railCamera_->addRot(Rot);
			railCamera_->setTranslation({ vector.x * 750 * 2 + vector.x * 10,0.0f,vector.z * 10 });

			currentSide = side::Fifth;
		}
		break;
	case side::Fifth:
		if (player.z > rotRange[4])
		{
			Vector3 move = { -vector.x * spped,-vector.y * spped,-vector.z * spped };
			railCamera_->addTranslation({ move });
		}
		else if (player.z <= rotRange[4])
		{
			Vector3 Rot = { 0,120 * affine::Deg2Rad,0 };
			/*Vector3 move = { 0,0,0 };
			move.x = player.x + cosf(Rot.y - affine::PIHalf);
			move.z = player.z - sinf(Rot.y - affine::PIHalf);
			move -= railCamera_->GetWorldTransformPtr()->translation_;
			float len = sqrt(move.x * move.x + move.y * move.y + move.z * move.z);
			if (len != 0)
			{
				move /= len;
			}*/
			railCamera_->addRot(Rot);
			railCamera_->setTranslation({ vector.x * 750 + vector.x * 10,0,rotRange[4] - vector.z * 10 });

			currentSide = side::Sixth;
		}
		break;
	case side::Sixth:
		if (player.z < rotRange[5])
		{
			Vector3 move = { -vector.x * spped,vector.y * spped,vector.z * spped };
			railCamera_->addTranslation({ move });
		}
		else if (player.z >= rotRange[5])
		{
			Vector3 Rot = { 0,30 * affine::Deg2Rad,0 };
			/*Vector3 move = { 0,0,0 };
			move.x = player.x + cosf(Rot.y - affine::PIHalf);
			move.z = player.z - sinf(Rot.y - affine::PIHalf);
			move -= railCamera_->GetWorldTransformPtr()->translation_;
			float len = sqrt(move.x * move.x + move.y * move.y + move.z * move.z);
			if (len != 0)
			{
				move /= len;
			}*/
			railCamera_->addRot(Rot);
			railCamera_->setTranslation({ 0.0,0.0f,-10.0f });

			currentSide = side::First;
		}
		break;
	default:
		break;
	}

	railCamera_->Update(player_->GetWorldTransform());

	player_->Update();

	resultCamera_->Update();

	objectManager_->Update();

	debugText_->SetPos(10, 10);
	debugText_->Printf(" %f, %f, %f", player.x, player.y, player.z);
	debugText_->SetPos(10, 30);
	debugText_->Printf(" %d", spped);
	debugText_->SetPos(10, 50);
	debugText_->Printf(" %d", currentSide);
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

	player_->GetCollider().DebugDraw();

	objectManager_->DebugDraw();
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
