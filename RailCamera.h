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
	bool Update(bool GetCrashFlag);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �^�C�g������Q�[���Ɉڍs����Ƃ��Ƀ��Z�b�g����
	/// </summary>
	void reset();

	void SpeedUp();

	void SpeedDown();

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

	//���������������H
	bool isActivationDoor = false;

	void Move();
};

