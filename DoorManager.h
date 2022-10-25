#pragma once
#include "door.h"
#include<memory>
class DoorManager
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 vector);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(int frequencyInvocationDoor);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection* ViewProjection);

	/// <summary>
/// スプライト用描画
/// </summary>
	void SpriteDraw();

	void  Reset();

	bool GetMashFlag(int frequencyInvocationDoor);

private:
	std::unique_ptr<door> door_[4]={};
	
	Vector3 vector_;

	uint32_t textureHandle_ = 0;
	std::unique_ptr<Sprite> sprite_;
};

