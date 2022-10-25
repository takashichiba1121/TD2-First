#include<cmath>
#include"affine.h"

//単位行列
void affine::makeMatIdentity(Matrix4& matrix)
{
	matrix = {
	   1.0f,0,0,0,
	   0,1.0f,0,0,
	   0,0,1.0f,0,
	   0,0,0,1.0f,
	};
}

//アフィン変換拡縮
void affine::makeMatScale(Matrix4& matrix, Vector3 scale)
{
	Matrix4 matScale;
	makeMatIdentity(matScale);
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;
	matrix *= matScale;
}

//アフィン変換回転
void affine::makeMatRot(Matrix4& matrix, Vector3 rot)
{
	Matrix4 matrotX;
	makeMatIdentity(matrotX);
	matrotX.m[1][1] = cos(rot.x);
	matrotX.m[1][2] = sin(rot.x);
	matrotX.m[2][1] = -sin(rot.x);
	matrotX.m[2][2] = cos(rot.x);

	Matrix4 matrotY;
	makeMatIdentity(matrotY);
	matrotY.m[0][0] = cos(rot.y);
	matrotY.m[0][2] = -sin(rot.y);
	matrotY.m[2][0] = sin(rot.y);
	matrotY.m[2][2] = cos(rot.y);

	Matrix4 matrotZ;
	makeMatIdentity(matrotZ);
	matrotZ.m[0][0] = cos(rot.z);
	matrotZ.m[0][1] = sin(rot.z);
	matrotZ.m[1][0] = -sin(rot.z);
	matrotZ.m[1][1] = cos(rot.z);

	Matrix4 matRot;
	makeMatIdentity(matRot);

	matRot *= matrotZ;
	matRot *= matrotX;
	matRot *= matrotY;
	matrix *= matRot;
}

//アフィン変換平行移動
void affine::makeMatTrans(Matrix4& matrix, Vector3 trans)
{
	Matrix4  matTrams;
	makeMatIdentity(matTrams);
	matTrams.m[3][0] = trans.x;
	matTrams.m[3][1] = trans.y;
	matTrams.m[3][2] = trans.z;

	matrix *= matTrams;
}

void affine::makeAffine(WorldTransform& worldTransform)
{
	makeMatIdentity(worldTransform.matWorld_);
	makeMatScale(worldTransform.matWorld_, worldTransform.scale_);
	makeMatRot(worldTransform.matWorld_, worldTransform.rotation_);
	makeMatTrans(worldTransform.matWorld_, worldTransform.translation_);
}

Vector3 affine::MatVector(Matrix4 matrix, Vector3 vector)
{
	Vector3 matVector = { 0,0,0 };
	matVector.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0];
	matVector.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1];
	matVector.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2];
	return matVector;
}
Vector3 affine::Mat3D(Matrix4 matrix, Vector3 vector)
{
	Vector3 matVector = { 0,0,0 };
	matVector.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] * 1 * matrix.m[3][0];
	matVector.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] * 1 * matrix.m[3][1];
	matVector.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] * 1 * matrix.m[3][2];
	return matVector;
}
Vector3 affine::GetWorldTrans(Matrix4 matrix)
{
	Vector3 mattrans;
	mattrans.x = matrix.m[3][0];
	mattrans.y = matrix.m[3][1];
	mattrans.z = matrix.m[3][2];
	return mattrans;
}
Vector3 affine::wdivision(Matrix4 matrix, Vector3 vector)
{
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	Vector3 result
	{
		(vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0]) / w,
		(vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1]) / w,
		(vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2]) / w
	};

	return result;
}

void AABB::DebugDraw()
{
	Vector4 col = { 1.0f,1.0f,1.0f,1.0f };

	//上
	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x - size.x, center.y + size.y, center.z + size.z },
		{ center.x + size.x, center.y + size.y, center.z + size.z },
		col);

	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x - size.x, center.y + size.y, center.z - size.z },
		{ center.x + size.x, center.y + size.y, center.z - size.z },
		col);

	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x + size.x, center.y + size.y, center.z + size.z },
		{ center.x + size.x, center.y + size.y, center.z - size.z },
		col);

	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x - size.x, center.y + size.y, center.z + size.z },
		{ center.x - size.x, center.y + size.y, center.z - size.z },
		col);

	//下
	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x - size.x, center.y - size.y, center.z + size.z },
		{ center.x + size.x, center.y - size.y, center.z + size.z },
		col);

	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x - size.x, center.y - size.y, center.z - size.z },
		{ center.x + size.x, center.y - size.y, center.z - size.z },
		col);

	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x + size.x, center.y - size.y, center.z + size.z },
		{ center.x + size.x, center.y - size.y, center.z - size.z },
		col);

	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x - size.x, center.y - size.y, center.z + size.z },
		{ center.x - size.x, center.y - size.y, center.z - size.z },
		col);

	//縦
	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x - size.x, center.y + size.y, center.z + size.z },
		{ center.x - size.x, center.y - size.y, center.z + size.z },
		col);

	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x - size.x, center.y + size.y, center.z - size.z },
		{ center.x - size.x, center.y - size.y, center.z - size.z },
		col);

	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x + size.x, center.y + size.y, center.z + size.z },
		{ center.x + size.x, center.y - size.y, center.z + size.z },
		col);

	PrimitiveDrawer::GetInstance()->DrawLine3d(
		{ center.x + size.x, center.y + size.y, center.z - size.z },
		{ center.x + size.x, center.y - size.y, center.z - size.z },
		col);
}

bool CheckAABB2AABB(AABB& aabb1, AABB& aabb2)
{
	std::array<Vector3, 2> min_;
	min_[0] = { aabb1.center.x - aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	min_[1] = { aabb2.center.x - aabb2.size.x, aabb2.center.y - aabb2.size.y ,aabb2.center.z - aabb2.size.z };
	std::array<Vector3, 2> max_;
	max_[0] = { aabb1.center.x + aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z + aabb1.size.z };
	max_[1] = { aabb2.center.x + aabb2.size.x, aabb2.center.y + aabb2.size.y ,aabb2.center.z + aabb2.size.z };

	if (min_[0].x > max_[1].x || max_[0].x < min_[1].x ||
		min_[0].y > max_[1].y || max_[0].y < min_[1].y ||
		min_[0].z > max_[1].z || max_[0].z < min_[1].z)
	{
		return false;
	}

	return true;
}

bool CheckAABB2SPHERE(AABB& aabb1, SPHERE& sphere)
{
	std::array<Vector3, 8> vex;

	vex[0] = { aabb1.center.x - aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	vex[1] = { aabb1.center.x - aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z + aabb1.size.z };
	vex[2] = { aabb1.center.x + aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	vex[3] = { aabb1.center.x + aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z + aabb1.size.z };

	vex[4] = { aabb1.center.x - aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	vex[5] = { aabb1.center.x - aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z + aabb1.size.z };
	vex[6] = { aabb1.center.x + aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	vex[7] = { aabb1.center.x + aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z + aabb1.size.z };

	for (Vector3 v : vex)
	{
		float ren = (fabs(v.x - sphere.center.x)) * 2 + (fabs(v.y - sphere.center.y)) * 2 + (fabs(v.z - sphere.center.z)) * 2;

		if (fabs(ren) < sphere.radius * 2)
		{
			return true;
		}

	}

	return false;
}