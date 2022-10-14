#include "ResultCamera.h"
#include"affine.h"

ResultCamera::ResultCamera()
{
}

ResultCamera::~ResultCamera()
{
}

void ResultCamera::Initialize(WorldTransform* worldTransform)
{

	using namespace MathUtility;

	worldTransform_.parent_ = worldTransform;

	//ワールドトランスフォームの初期設定
	worldTransform_.translation_ = {1.0f,-2.0f,11.0f};
	worldTransform_.rotation_ = {0.0,225.0f*affine::Deg2Rad,0.0f};

	viewProjection_ = std::make_unique<ViewProjection>();
	//ビュープロジェクションの初期化
	viewProjection_->Initialize();
}

void ResultCamera::Update()
{
	using namespace MathUtility;

	affine::makeAffine(worldTransform_);

	worldTransform_.matWorld_*= worldTransform_.parent_->matWorld_;

	viewProjection_->eye = affine::GetWorldTrans(worldTransform_.matWorld_);
	//ワールド前方ベクトル
	Vector3 forward(0, 0, 1);
	//レールカメラの回転を反映
	forward = affine::MatVector(worldTransform_.matWorld_, forward);
	//視点から前方に適当な距離進んだ位置が注視点
	viewProjection_->target = viewProjection_->eye + forward;
	//ワールド上方ベクトル
	Vector3 up(0, 1, 0);
	//レールカメラの回転を反映(レールカメラの上方ベクトル)
	viewProjection_->up = affine::MatVector(worldTransform_.matWorld_, up);
	//ビュープロジェクションを更新
	viewProjection_->UpdateMatrix();
	viewProjection_->TransferMatrix();
}

void ResultCamera::Draw() {}

ViewProjection* ResultCamera::GetViewProjection()
{
	return viewProjection_.get();
}

WorldTransform* ResultCamera::GetWorldTransformPtr()
{
	return &worldTransform_;
}