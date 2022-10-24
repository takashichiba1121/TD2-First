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
	/// ������
	/// </summary>
	void Initialize(WorldTransform* worldTransform);

	/// <summary>
	/// �Q�[�����̖��t���[������
	/// </summary>
	void Update();
	/// <summary>
	/// �Q�[���ȊO�̖��t���[������
	/// </summary>
	void titleUpdate();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	WorldTransform GetWorldTransform() { return worldTransform_; };

	AABB& GetCollider();

	void OnCollision();

	bool GetCrashFlag();

	void SetTransform(Vector3 translation) { worldTransform_.translation_=translation; }

private:

	void Move();

	void Rotate();

	void Complement(float& x1, float x2, float flame);

	void Jump();

	void Squat();

	uint8_t jumpFlag = 0u;

	float gravitySpeed = 0.5;
	float defGravitySpeed = gravitySpeed;

	bool crashFlag = false;

	uint32_t crashTime = 70;
	AABB collider_;

	//��]�^�����~�߂�
	bool rollStopFlag = false;

	//���Ⴊ�݃t���O
	bool squatFlag = false;

	Vector3 oldRot;
	uint32_t squatTime = 60 * 2;
	float oldRotY = 0.0f;
	//���f��
	std::unique_ptr<Model> model_;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

};

