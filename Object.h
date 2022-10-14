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
	void Initialize(Vector3 pos,Vector3 size, Model* model);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(Vector3 playerPos);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	//�R���C�_�[����
	AABB& GetCollider();

	//�����������̊֐�
	void OnCollision();


	bool GetIsDeath();

private:
	bool IsDeath;
	AABB collider_;
	Model* model_;
	std::unique_ptr<WorldTransform> worldTransform_;
};

bool CheckAABB2AABB(AABB& aabb1, AABB& aabb2);

