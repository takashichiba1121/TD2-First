#pragma once
#include"MathUtility.h"
#include"Model.h"
#include<memory>

class BranchPoint
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Vector3& pos, Vector3& rot);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* viewProjection);
private:
	//�{��
	std::unique_ptr<Model> bodyMode_;
	std::unique_ptr<WorldTransform> bodyWorldTransform_;

	//����
	std::unique_ptr<Model> correctMode_;
	std::unique_ptr<WorldTransform> correctWorldTransform_;

	//�s����
	std::unique_ptr<Model> wrongMode_;
	std::unique_ptr<WorldTransform> wrongWorldTransform_;

};

