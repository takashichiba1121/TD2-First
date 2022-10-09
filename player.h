#pragma once
#include<memory>
#include"Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"

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

	//���f��
	std::unique_ptr<Model> model_;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

};

