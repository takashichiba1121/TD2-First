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
	void Initialize(const Vector3& pos, float radius, Model* model);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	//コライダー所得
	SPHERE& GetCollider();

	//当たった時の関数
	void OnCollision();


	bool GetIsDeath();

private:
	bool IsDeath;
	SPHERE collider_;
	Model* model_;
	std::unique_ptr<WorldTransform> worldTransform_;
};


