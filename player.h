#pragma once
#include<memory>
#include"Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"Input.h"
#include"affine.h"

class Player
{
public:
	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WorldTransform* worldTransform);

	/// <summary>
	/// ゲーム中の毎フレーム処理
	/// </summary>
	void Update();
	/// <summary>
	/// ゲーム以外の毎フレーム処理
	/// </summary>
	void titleUpdate();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	WorldTransform GetWorldTransform() { return worldTransform_; };

	AABB& GetCollider();

	void OnCollision();

	bool GetCrashFlag();

	void SetTransform(Vector3 translation) { worldTransform_.translation_=translation; }

private:

	void Move();

	void Rotate();

	void Complement(float& x1, float x2, float flame);

	void Jump();

	void Squat();

	uint8_t jumpFlag = 0u;

	float gravitySpeed = 0.5;
	float defGravitySpeed = gravitySpeed;

	bool crashFlag = false;

	uint32_t crashTime = 70;
	AABB collider_;

	//回転運動を止める
	bool rollStopFlag = false;

	//しゃがみフラグ
	bool squatFlag = false;

	Vector3 oldRot;
	uint32_t squatTime = 60 * 2;
	float oldRotY = 0.0f;
	//モデル
	std::unique_ptr<Model> model_;
	//ワールド変換データ
	WorldTransform worldTransform_;

};

