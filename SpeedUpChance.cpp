#include "SpeedUpChance.h"

void SpeedUpChance::Initialize(RailCamera* railCamera)
{
	bodyModel_.reset(Model::CreateFromOBJ("branchPoint"));

	/*std::unique_ptr<BranchPoint> branchPoint;
	branchPoint = std::make_unique<BranchPoint>();

	branchPoint->Initialize({ 0.0f,-10.0f,300.0f },{ 0.0f,0.0f,0.0f },{1.0f,1.5f,0.01f},
		bodyModel_.get(),
		std::bind(&RailCamera::SpeedDown, railCamera), std::bind(&RailCamera::SpeedUp, railCamera));

	branchPoints.push_back(std::move(branchPoint));*/
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
