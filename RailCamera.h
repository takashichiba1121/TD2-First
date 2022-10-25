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
	/// ������
	/// </summary>
	void Initialize(const Vector3& position, const Vector3& rotaion);

	/// <summary>
	/// ���t���[������
	/// </summary>
	bool Update(bool GetCrashFlag,int frequencyInvocationDoor);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �^�C�g������Q�[���Ɉڍs����Ƃ��Ƀ��Z�b�g����
	/// </summary>
	void reset();

	/// <summary>
	/// ������邲�ƂɃ��Z�b�g���郂�m���܂Ƃ߂�
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
		First = 1,//���
		Second,//���
		Third,//�O��
		Fourth,//�l��
		Fifth,//�ܔ�
		Sixth//�Z��
	};

	side currentSide = side::First;

	int lap = 0;

	bool IsLapReset = false;

	void Move();

	float invocationTrnsDoor[4]={};
};

