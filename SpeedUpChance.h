#pragma once
#include"affine.h"
#include<list>
#include"BranchPoint.h"

class SpeedUpChance
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(RailCamera* railCamera);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(Player* player, RailCamera* railCamera);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection* viewProjection);

	void DebugDraw();

private:
	std::list<std::unique_ptr<BranchPoint>>branchPoints;

	//�{��
	std::unique_ptr<Model> bodyModel_;

	//����
	std::unique_ptr<Model> correctModel_;

	//�s����
	std::unique_ptr<Model> wrongModel_;

};

