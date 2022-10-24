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
	/// ������
	/// </summary>
	void Initialize(const Vector3& pos, float radius, Model* model);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	//�R���C�_�[����
	SPHERE& GetCollider();

	//�����������̊֐�
	void OnCollision();


	bool GetIsDeath();

private:
	bool IsDeath;
	SPHERE collider_;
	Model* model_;
	std::unique_ptr<WorldTransform> worldTransform_;
};


