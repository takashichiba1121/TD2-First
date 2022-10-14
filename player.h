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
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	WorldTransform GetWorldTransform() { return worldTransform_; };

	AABB& GetCollider();

	void OnCollision();

private:

	void Move();

	void Rotate();

	void Complement(float& x1, float x2, float flame);

	void Jump();

	uint8_t jumpFlag = 0u;

	float gravitySpeed = 0.5;
	float defGravitySpeed = gravitySpeed;

	AABB collider_;

	//モデル
	std::unique_ptr<Model> model_;
	//ワールド変換データ
	WorldTransform worldTransform_;

};

