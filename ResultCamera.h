#pragma once

#include"ViewProjection.h"
#include"WorldTransform.h"
#include"affine.h"

#include<memory>

class ResultCamera
{
public:

	ResultCamera();
	~ResultCamera();

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
	void Draw();

	ViewProjection* GetViewProjection();

	WorldTransform* GetWorldTransformPtr();

	void addRot(Vector3 rot) { worldTransform_.rotation_ += rot; };
	void addTranslation(Vector3 translation) { worldTransform_.translation_ += translation; };

	void setTranslation(Vector3 translation) { worldTransform_.translation_ = translation; };

private:

	std::unique_ptr<ViewProjection> viewProjection_;

	WorldTransform worldTransform_;
};
