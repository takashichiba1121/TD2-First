#pragma once
#include<list>
#include<memory>
#include<Model.h>
#include"WorldTransform.h"
#include"ViewProjection.h"

class Object
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Vector3 pos);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(Vector3 playerPos);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* ViewProjection);
private:

	std::unique_ptr<Model> model_;
	std::unique_ptr<WorldTransform> worldTransform_;
};

