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
	bool Update(bool GetCrashFlag,int frequencyInvocationDoor);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// タイトルからゲームに移行するときにリセットする
	/// </summary>
	void reset();

	/// <summary>
	/// 一周するごとにリセットするモノをまとめる
	/// </summary>
	void lapReset();

	void SpeedUp();

	void SpeedDown();

	ViewProjection* GetViewProjection();

	WorldTransform* GetWorldTransformPtr();

	float GetWorldTransformRot();

	int GetLap() {return lap; }

	void setTranslation(Vector3 translation) { worldTransform_.translation_ = translation; };

	void setSpeed(float speed) { this->speed = speed; }

	bool GetIsRapReset() { return IsLapReset; }

	Vector3 GetVector() { return vector; }

private:

	DebugText* debugText_ = nullptr;

	std::unique_ptr<ViewProjection> viewProjection_;
	WorldTransform worldTransform_;

	Vector3 vector = { 0,0,0 };

	float rotRange[6] = {};

	float speed = 1.0f;

	enum class side {
		First = 1,//一番
		Second,//二番
		Third,//三番
		Fourth,//四番
		Fifth,//五番
		Sixth//六番
	};

	side currentSide = side::First;

	int lap = 0;

	bool IsLapReset = false;

	void Move();

	float invocationTrnsDoor[4]={};
};

