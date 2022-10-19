#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"
#include"affine.h"
#include<DebugText.h>

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
	void Update(bool GetCrashFlag);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	ViewProjection* GetViewProjection();

	WorldTransform* GetWorldTransformPtr();

	float GetWorldTransformRot();

	void addRot(Vector3 rot) { worldTransform_.rotation_ += rot; };
	void addTranslation(Vector3 translation) { worldTransform_.translation_ += translation; };

	void setTranslation(Vector3 translation) { worldTransform_.translation_ = translation; };

private:

	DebugText* debugText_ = nullptr;

	std::unique_ptr<ViewProjection> viewProjection_;
	WorldTransform worldTransform_;

	Vector3 vector = { 0,0,0 };
	Vector3 playerVector = { 0,0,0 };

	float rotRange[6] = {};

	int speed = 1;

	enum class side {
		First = 1,//一番
		Second,//二番
		Third,//三番
		Fourth,//四番
		Fifth,//五番
		Sixth//六番
	};

	side currentSide = side::First;

	void Move();
};

