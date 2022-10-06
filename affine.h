#pragma once

#include "WorldTransform.h"

namespace affine
{
	//�P�ʍs��
	void makeMatIdentity(Matrix4& matrix);

	//�A�t�B���ϊ��g�k
	void makeMatScale(Matrix4& matrix, Vector3 scale);

	//�A�t�B���ϊ���]
	void makeMatRot(Matrix4& matrix, Vector3 rot);

	//�A�t�B���ϊ����s�ړ�
	void makeMatTrans(Matrix4& matrix, Vector3 Trans);

	//�x�N�g���ƍs��̊|���Z
	Vector3 MatVector(Matrix4 matrix, Vector3 vector);

	Vector3 Mat3D(Matrix4 matrix, Vector3 vector);
	//���[���h���W��Ԃ�
	Vector3 GetWorldTrans(Matrix4 matrix);

	Vector3 wdivision(Matrix4 matrix, Vector3 vector);
}