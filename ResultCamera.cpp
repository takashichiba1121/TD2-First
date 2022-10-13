#include "ResultCamera.h"

ResultCamera::ResultCamera()
{
}

ResultCamera::~ResultCamera()
{
}

void ResultCamera::Initialize(const Vector3& position, const Vector3& rotaion)
{
	//ワールドトランスフォームの初期設定
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotaion;

	viewProjection_ = std::make_unique<ViewProjection>();
	//ビュープロジェクションの初期化
	viewProjection_->Initialize();
}

void ResultCamera::Update(WorldTransform worldTransform)
{
	using namespace MathUtility;


	Vector3 move(0, 0, 0);
	Vector3 front;
	Vector3 frontVec;
	Vector3 frontNormVec;

	float rotationSpeed = 0.01f;

	front.x = worldTransform.translation_.x + cosf(worldTransform.rotation_.y - affine::PIHalf);
	front.y = worldTransform.translation_.y + cosf(worldTransform.rotation_.x - affine::PIHalf);
	front.z = worldTransform.translation_.z - sinf(worldTransform.rotation_.y - affine::PIHalf);


	frontVec = front - worldTransform.translation_;
	frontNormVec = MathUtility::Vector3Normalize(frontVec);
	frontVec = frontNormVec;

	float speed_ = 0.01f;

	Vector3 moveSpeed_ = speed_ * frontNormVec;

	//ワールドトランスフォームの数値を加算
	worldTransform.translation_.x += moveSpeed_.x;
	worldTransform.translation_.y += moveSpeed_.y;
	worldTransform.translation_.z += moveSpeed_.z;

	//ワールドトランスフォームの更新
	affine::makeAffine(worldTransform_);

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