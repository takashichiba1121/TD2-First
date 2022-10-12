#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"
#include"affine.h"

#include<memory>

class RailCamera
{
public:

	RailCamera();
	~RailCamera();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& position, const Vector3& rotaion);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(WorldTransform worldTransform);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	ViewProjection* GetViewProjection();

	WorldTransform* GetWorldTransformPtr();

	void addRot(Vector3 rot) { worldTransform_.rotation_ += rot; };
	void addtranslation(Vector3 translation) { worldTransform_.translation_ += translation; };

private:

	std::unique_ptr<ViewProjection> viewProjection_;

	WorldTransform worldTransform_;
};

