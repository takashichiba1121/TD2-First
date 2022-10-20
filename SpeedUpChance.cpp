#include "SpeedUpChance.h"

void SpeedUpChance::Initialize(RailCamera* railCamera)
{
	correctModel_.reset(Model::Create());
	bodyModel_.reset(Model::Create());
	wrongModel_.reset(Model::Create());

	std::unique_ptr<BranchPoint> branchPoint;
	branchPoint = std::make_unique<BranchPoint>();

	branchPoint->Initialize({ 0,-3,300 },{ 0,0,0 },{9.5,2.0f,0.01},
		bodyModel_.get(), correctModel_.get(), wrongModel_.get(),
		std::bind(&RailCamera::SpeedDown, railCamera), std::bind(&RailCamera::SpeedUp, railCamera));

	branchPoints.push_back(std::move(branchPoint));
}

void SpeedUpChance::Update(Player* player, RailCamera* railCamera)
{
	for (std::unique_ptr<BranchPoint>& branchPoint : branchPoints)
	{
		branchPoint->Update(player, railCamera);
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
