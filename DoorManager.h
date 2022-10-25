#pragma once
#include "door.h"
#include<memory>
class DoorManager
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Vector3 vector);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(int frequencyInvocationDoor);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* ViewProjection);

	/// <summary>
/// �X�v���C�g�p�`��
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

