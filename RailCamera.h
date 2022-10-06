#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"
#include"affine.h"

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
	void Update(Vector3& move, Vector3& rot);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	ViewProjection* GetViewProjection();

	WorldTransform* GetWorldTransformPtr();

private:

	std::unique_ptr<ViewProjection> viewProjection_;

	WorldTransform worldTransform_;
};

