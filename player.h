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
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* viewProjection);

private:

	void Move();

	void Rotate();

	void Complement(float& x1, float x2, float flame);

	float defAngle = 90.0f * affine::Deg2Rad;

	//���f��
	std::unique_ptr<Model> model_;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

};

