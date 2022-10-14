#pragma once
#include<list>
#include<memory>
#include<Model.h>
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"affine.h"
class Object
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 pos,Vector3 size, Model* model);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Vector3 playerPos);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	//コライダー所得
	AABB& GetCollider();

	//当たった時の関数
	void OnCollision();


	bool GetIsDeath();

private:
	bool IsDeath;
	AABB collider_;
	Model* model_;
	std::unique_ptr<WorldTransform> worldTransform_;
};

bool CheckAABB2AABB(AABB& aabb1, AABB& aabb2);

