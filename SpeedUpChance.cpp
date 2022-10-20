#include "SpeedUpChance.h"

void SpeedUpChance::Initialize(RailCamera* railCamera)
{
	correctModel_.reset(Model::Create());
	bodyModel_.reset(Model::Create());
	wrongModel_.reset(Model::Create());

	std::unique_ptr<BranchPoint> branchPoint;
	branchPoint = std::make_unique<BranchPoint>();

	branchPoint->Initialize({ 0.0f,-3.0f,300.0f },{ 0.0f,0.0f,0.0f },{9.5f,2.0f,0.01f},
		bodyModel_.get(), correctModel_.get(), wrongModel_.get(),
		std::bind(&RailCamera::SpeedDown, railCamera), std::bind(&RailCamera::SpeedUp, railCamera));

	branchPoints.push_back(std::move(branchPoint));
}

void SpeedUpChance::Update(Player* player)
{
	for (std::unique_ptr<BranchPoint>& branchPoint : branchPoints)
	{
		branchPoint->Update(player);
	}
}

void SpeedUpChance::Draw(ViewProjection* viewProjection)
{
	for (std::unique_ptr<BranchPoint>& branchPoint : branchPoints)
	{
		branchPoint->Draw(viewProjection);
	}
}

void SpeedUpChance::DebugDraw()
{
	for (std::unique_ptr<BranchPoint>& branchPoint : branchPoints)
	{
		branchPoint->DebugDraw();
	}
}
